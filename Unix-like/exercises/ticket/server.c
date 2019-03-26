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

#define oops(m){perror(m);exit(EXIT_FAILURE);}
#define PORT "13194"
#define KEYLEN 24

struct ticket
{
	char key[KEYLEN];
	bool in_use;
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
	a->head->in_use = false;
	a->head->next = NULL;
	snprintf(a->head->key,KEYLEN,"%s",buf);
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
			tmp->in_use = false;
			snprintf(tmp->key,KEYLEN,"%s",buf + i);
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

void receive_message_from_client(int sock_id,struct sockaddr_in *saddr,char cmd[],size_t cmdlen)
{
	socklen_t saddrlen = sizeof(struct sockaddr);
	memset(cmd,'\0',cmdlen);
	if(recvfrom(sock_id,cmd,cmdlen,0,(struct sockaddr *)saddr,&saddrlen) == -1)
		oops("server : rec");
}

void send_message_to_client(int sock_id,struct sockaddr_in *saddr,char *mesg,size_t mesglen)
{
	if(sendto(sock_id,mesg,mesglen,0,(struct sockaddr *)saddr,sizeof(struct sockaddr)) == -1)
		oops("server:sendto");
}

void grant_ticket(char *cmd,char *mesg,struct agent ticket_agent)
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

void reclaim_ticket(char *cmd,char *mesg,struct agent ticket_agent)
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

void verify_ticket(char *cmd,char *mesg,struct agent ticket_agent)
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

void server_handler(char *cmd,char *mesg,size_t *mesglen,struct agent ticket_agent)
{
	memset(mesg,'\0',*mesglen);
	if(strncmp(cmd,"GRANT",5) == 0)
		grant_ticket(cmd + 6,mesg,ticket_agent);
	else if(strncmp(cmd,"GBYE",4) == 0)
		reclaim_ticket(cmd + 5,mesg,ticket_agent);
	else if(strncmp(cmd,"VALID",5) == 0)
		verify_ticket(cmd + 6,mesg,ticket_agent);
	else
		invalid_command(mesg);
	*mesglen = strlen(mesg);
}

void signal_handler(int signum)
{
	if(signum == SIGINT)
	{
		free_agent();
		close(sock_id);
		printf("shut down.\n");
		exit(SIGINT);
	}
	else if(signum == SIGALRM)
	{
		
	}
}

int main()
{
	char cmd[BUFSIZ],mesg[BUFSIZ];
	size_t cmdlen,mesglen;
	struct sockaddr_in saddr;

	init_agent(&ticket_agent);
	sock_id = make_server_socket_dgram(PORT);
	cmdlen = mesglen = BUFSIZ;
	signal(SIGALRM,signal_handler);
	signal(SIGINT,signal_handler);
	while(1)
	{
		/* printf_keys(ticket_agent); */
		receive_message_from_client(sock_id,&saddr,cmd,cmdlen);
		printf("%s:%d,%s\n",inet_ntoa(saddr.sin_addr),saddr.sin_port,cmd);
		server_handler(cmd,mesg,&mesglen,ticket_agent);
		send_message_to_client(sock_id,&saddr,mesg,mesglen);
	}
	free_agent();
}
