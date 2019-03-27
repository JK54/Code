#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#define oops(m){perror(m);exit(EXIT_FAILURE);}
#define PORT "13194"
#define KEYLEN 24
#define VALIDATE_INTERVAL 2

struct ticket
{
	char key[KEYLEN];
	bool in_use;
	struct sockaddr_in saddr;
	struct ticket *next;
};

struct agent
{
	struct ticket *head;
	int ticket_total;
	int ticket_remnant;
};

struct agent ticket_agent;
int sock_id;

void init_agent(struct agent *a)
{
	FILE *key_importer;
	char buf[BUFSIZ];
	struct ticket *tmp;
	size_t size;

	key_importer = fopen("./licenses.dat","r");
	size = sizeof(struct ticket);
	fread(buf,sizeof(char),KEYLEN,key_importer);
	a->head = malloc(size);
	a->head->next = NULL;
	snprintf(a->head->key,KEYLEN,"%s",buf);
	a->head->in_use = false;
	memset(&(a->head->saddr),0,sizeof(a->head->saddr));
	a->ticket_remnant = 1;
	tmp = a->head;
	while(fread(buf,sizeof(char),BUFSIZ,key_importer) > 0)
	{
		size_t len = strlen(buf);
		for(int i = 0;i < len;i += 24)
		{
			tmp->next = malloc(size);
			tmp = tmp->next;
			tmp->next = NULL;
			snprintf(tmp->key,KEYLEN,"%s",buf + i);
			tmp->in_use = false;
			memset(&(tmp->saddr),0,sizeof(tmp->saddr));
			a->ticket_remnant++;
		}
	}
	a->ticket_total = a->ticket_remnant;
	fclose(key_importer);
}

void free_agent()
{
	struct ticket *tmp = ticket_agent.head;
	struct ticket *pre = tmp;
	while(tmp != NULL)
	{
		tmp = pre->next;
		free(pre);
		pre = tmp;
	}
	ticket_agent.ticket_remnant = 0;
}


void printf_keys(struct agent a)
{
	struct ticket *tmp = a.head;
	while(tmp != NULL)
	{
		printf("%s:%d\n",tmp->key,tmp->in_use);
		tmp = tmp->next;
	}
	printf("\n");
}

int make_server_socket_dgram(char *servname)
{
	int sock_id;
	struct addrinfo hint,*res;
	int addrno;
	char hostname[BUFSIZ];

	if((sock_id = socket(AF_INET,SOCK_DGRAM,0)) == -1)
		oops("socket");
	memset(&hint,0,sizeof(hint));
	hint.ai_flags = AI_PASSIVE;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_DGRAM;
	snprintf(hostname,BUFSIZ,"%d",INADDR_ANY);
	if((addrno = getaddrinfo(hostname,servname,&hint,&res)) != 0)
	{
		printf("%s\n",gai_strerror(addrno));
		oops("getaddrinfo");
	}
	if(bind(sock_id,res->ai_addr,sizeof(struct sockaddr)) == -1)
		oops("bind");
	return sock_id;
}

int syslog(int fd,char *mesg,struct sockaddr_in *saddr)
{
	char buf[BUFSIZ];
	snprintf(buf,BUFSIZ,"%s:%d,%s.\n\n",inet_ntoa(saddr->sin_addr),saddr->sin_port,mesg);
	return write(fd,buf,strlen(buf));
}

void receive_from_client(int sock_id,struct sockaddr_in *saddr,char cmd[],size_t *cmdlen)
{
	socklen_t saddrlen = sizeof(struct sockaddr);
	memset(cmd,'\0',*cmdlen);
	if((*cmdlen = recvfrom(sock_id,cmd,*cmdlen,0,(struct sockaddr *)saddr,&saddrlen)) == -1)
		oops("server : rec");
	syslog(STDOUT_FILENO,cmd,saddr);
}

void send_to_client(int sock_id,struct sockaddr_in *saddr,char *mesg,size_t mesglen)
{
	if(sendto(sock_id,mesg,mesglen,0,(struct sockaddr *)saddr,sizeof(struct sockaddr)) == -1)
		oops("server:sendto");
	syslog(STDOUT_FILENO,mesg,saddr);
}

void grant_ticket(char *cmd,char *mesg,struct sockaddr_in *saddr,struct agent ticket_agent)
{
	struct ticket *tmp = ticket_agent.head;
	while(tmp != NULL)
	{
		if(strncmp(cmd,tmp->key,KEYLEN) == 0)
		{
			if(tmp->in_use == false)
			{
				snprintf(mesg,strlen("TICK\n") + strlen(tmp->key) + strlen(" granted.") + 1,"TICK\n%s granted.",tmp->key);
				tmp->in_use = true;
				memcpy(&tmp->saddr,saddr,sizeof(struct sockaddr_in));
			}
			else
				snprintf(mesg,strlen("ALDYTICK\n") + strlen(tmp->key) + strlen(" already occupied.") + 1,"ALDYTICK\n%s already occupied.",tmp->key);
			break;
		}
		tmp = tmp->next;
	}
	if(tmp == NULL)
		snprintf(mesg,strlen("FAIL\n") +  strlen(cmd) + strlen(" is invalid.") + 1,"FAIL\n%s is invalid.",cmd);
}

void reclaim_ticket(char *cmd,char *mesg,struct sockaddr_in *saddr,struct agent ticket_agent)
{
	struct ticket *tmp = ticket_agent.head;
	while(tmp != NULL)
	{
		if(strncmp(cmd,tmp->key,KEYLEN) == 0)
		{
			if(tmp->in_use == true)
			{
				snprintf(mesg,strlen("RECLAIM\n") + strlen(tmp->key) + strlen(" reclaimed.") + 1,"RECLAIM\n%s reclaimed.",tmp->key);
				tmp->in_use = false;
				memset(&tmp->saddr,0,sizeof(struct sockaddr_in));
			}
			else
				snprintf(mesg,strlen("ALDYRECLAIM\n") + strlen(tmp->key) + strlen(" already reclaimed.") + 1,"ALDYRECLAIM\n%s already reclaimed.",tmp->key);
			break;
		}
		tmp = tmp->next;
	}
	if(tmp == NULL)
		snprintf(mesg,strlen("FAIL\n") +  strlen(cmd) + strlen(" is invalid.") + 1,"FAIL\n%s  is invalid.",cmd);
}

void verify_ticket(char *cmd,char *mesg,struct sockaddr_in *saaddr,struct agent ticket_agent)
{
	struct ticket *tmp = ticket_agent.head;
	while(tmp != NULL)
	{
		if(strncmp(cmd,tmp->key,KEYLEN) == 0)
		{
			if(tmp->in_use == true)
			{
				snprintf(mesg,strlen("VALID\n") + strlen(tmp->key) + strlen(" is valid.") + 1,"VALID\n %s is valid.",tmp->key);
			}
			else
				snprintf(mesg,strlen("NOTGRANTED\n") + strlen(tmp->key) + strlen(" not granted.") + 1,"NOTGRANTED\n%s not granted.",tmp->key);
			break;
		}
		tmp = tmp->next;
	}
	if(tmp == NULL)
		snprintf(mesg,strlen("FAIL\n") +  strlen(cmd) + strlen(" is invalid.\n") + 1,"FAIL\n%s  is invalid.\n",cmd);
}

void invalid_command(char *mesg)
{
	snprintf(mesg,strlen("WRONGCMD\nyour request command is invalid.\n") + 1,"WRONGCMD\nyour request command is invalid.\n");
}

void check_user_alive()
{
	struct ticket *tmp = ticket_agent.head;
	while(tmp != NULL)
	{
		if(tmp->in_use == true)
		{
			char cmd[BUFSIZ],mesg[BUFSIZ];
			size_t mesglen = BUFSIZ;
			memset(cmd,'\0',BUFSIZ);
			memset(mesg,'\0',BUFSIZ);
			snprintf(cmd,BUFSIZ,"CHECK\n %s",tmp->key);
			send_to_client(sock_id,&tmp->saddr,cmd,strlen(cmd));
			receive_from_client(sock_id,&tmp->saddr,mesg,&mesglen);
			if(strncmp(mesg,"DEAD",4) == 0)
				tmp->in_use = false;
			syslog(sock_id,mesg,&tmp->saddr);
		}
		tmp = tmp->next;
	}
}

void server_handler(char *cmd,char *mesg,size_t *mesglen,struct sockaddr_in * saddr,struct agent ticket_agent)
{
	memset(mesg,'\0',*mesglen);
	if(strncmp(cmd,"GRANT",5) == 0)
		grant_ticket(cmd + 6,mesg,saddr,ticket_agent);
	else if(strncmp(cmd,"GBYE",4) == 0)
		reclaim_ticket(cmd + 5,mesg,saddr,ticket_agent);
	else if(strncmp(cmd,"VALID",5) == 0)
		verify_ticket(cmd + 6,mesg,saddr,ticket_agent);
	else
		invalid_command(mesg);
	*mesglen = strlen(mesg);
}

void free_source()
{
	close(sock_id);
	free_agent();
}

void set_validate_ticker(int sec)
{
	struct itimerval ticker;
	ticker.it_value.tv_sec = sec;
	ticker.it_value.tv_usec = 0;
	ticker.it_interval.tv_sec = sec;
	ticker.it_interval.tv_usec = 0;
	if(setitimer(ITIMER_REAL,&ticker,NULL) == -1)
		oops("set_validate_ticker");
}

void sigint_handler(int signum)
{
	free_source();
	printf("shut down.\n");
	exit(SIGINT);
}

void sigalarm_handler(int signum)
{
	signal(SIGALRM,sigalarm_handler);
	check_user_alive();
}

void signal_set()
{
	signal(SIGINT,sigint_handler);
	signal(SIGALRM,sigalarm_handler);
	set_validate_ticker(VALIDATE_INTERVAL);
}

int main()
{
	char cmd[BUFSIZ],mesg[BUFSIZ];
	size_t cmdlen,mesglen;
	struct sockaddr_in saddr;

	init_agent(&ticket_agent);
	sock_id = make_server_socket_dgram(PORT);
	signal_set();
	cmdlen = mesglen = BUFSIZ;
	while(1)
	{
		receive_from_client(sock_id,&saddr,cmd,&cmdlen);
		server_handler(cmd,mesg,&mesglen,&saddr,ticket_agent);
		send_to_client(sock_id,&saddr,mesg,mesglen);
	}
	free_source();
}
