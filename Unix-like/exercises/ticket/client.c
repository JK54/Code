#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#define oops(m){perror(m);exit(EXIT_FAILURE);}
#define SERVER "127.0.0.1"
#define SERVER_PORT "13194"
#define KEYLEN 24

char key[] = "VHIBO-CMDBY-EPJBW-Q5EMA";
int pid;

int make_client_socket_dgram();
void make_server_address(struct sockaddr_in *saddr,char *seraddress,char *servname);

int make_client_socket_dgram()
{
	int sock_id;
	if((sock_id = socket(AF_INET,SOCK_DGRAM,0)) == -1)
		oops("socket");
	return sock_id;
}

void make_server_address(struct sockaddr_in *saddr,char *seraddress,char *servname)
{
	struct addrinfo hint,*res;
	int addrno;
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_DGRAM;
	if((addrno = getaddrinfo(seraddress,servname,&hint,&res)) != 0)
	{
		printf("%s\n",gai_strerror(addrno));
		freeaddrinfo(res);
		oops("make_server_address");
	}
	memcpy(saddr,res->ai_addr,sizeof(struct sockaddr_in));
	freeaddrinfo(res);
}

void apply_permit_to_run(int sock_id,struct sockaddr_in saddr,char *mesg,size_t *mesglen)
{
	char cmd[KEYLEN + 6] = "GRANT ";
	strncat(cmd,key,KEYLEN);
	if(sendto(sock_id,cmd,strlen(cmd),0,(struct sockaddr *)&saddr,sizeof(saddr)) == -1)
		oops("GRANT");
	socklen_t tmp;
	if((*mesglen = recvfrom(sock_id,mesg,*mesglen,0,(struct sockaddr *)&saddr,&tmp)) == -1)
		oops("recv");
}

void receive_from_server(int sock_id,struct sockaddr_in *saddr,char cmd[],size_t *cmdlen)
{
	socklen_t saddrlen = sizeof(struct sockaddr);
	memset(cmd,'\0',*cmdlen);
	if((*cmdlen = recvfrom(sock_id,cmd,*cmdlen,0,(struct sockaddr *)saddr,&saddrlen)) == -1)
		oops("client : rec");
}
void alive(int sock_id,struct sockaddr_in *saddr,char *cmd)
{
	memset(cmd,'\0',strlen(cmd));
	if(kill(pid,0) == -1)
		snprintf(cmd,strlen(key) + 7,"DEAD\n %s",key);
	else
		snprintf(cmd,strlen(key) + 8,"ALIVE\n %s",key);
	sendto(sock_id,cmd,strlen(cmd),0,(struct sockaddr *)saddr,sizeof(struct sockaddr));
}

int super_sleep()
{
	if((pid = fork()) == -1)
		oops("fork");
	if(pid == 0)
	{
		execlp("./super_sleep","super_sleep",NULL);
		oops("super_sleep");
	}
	return pid;
}

void invalid_key()
{
	printf("The key being registered is invalid,contact the supplyer to get the valid license.\n");
	printf("The email : xxxxxxxxx@yy.xyz\n");
}

void duplicated_key()
{
	printf("The key being registered more than limit.\n");
	printf("Apply for a new lincense or shut down unneccessary user.\n");
}

void reclaim_key()
{
	printf("reclaim successed.\n");
}

void aldy_reclaim_key()
{
	printf("The key being reclaimed has already reclaimed.\n");
}

void not_granted_key()
{
	printf("the key being validated has not granted yet!\n");
}
void wrong_cmd()
{
	printf("the last cmd sento server is unknown.\n");
}

void client_handler(int sock_id,struct sockaddr_in *saddr,char *mesg,char *cmd)
{
	if(strncmp(mesg,"CHECK",5) == 0)
		alive(sock_id,saddr,cmd);
	else if(strncmp(mesg,"NOTGRANTED",10) == 0)
		not_granted_key();
	else if(strncmp(mesg,"TICK",4) == 0)
		super_sleep();
	else if(strncmp(mesg,"FAIL",4) == 0)
		invalid_key();
	else if(strncmp(mesg,"ALDYTICK",8) == 0)
		duplicated_key();
	else if(strncmp(mesg,"RECLAIM",7) == 0)
		reclaim_key();
	else if(strncmp(mesg,"ALDYRECLAIM",11) == 0)
		aldy_reclaim_key();
	else if(strncmp(mesg,"WRONGCMD",8) == 0)
		wrong_cmd();
}

int main()
{
	int sock_id;
	struct sockaddr_in saddr;
	char mesg[BUFSIZ];
	char cmd[BUFSIZ];
	size_t mesglen,cmdlen;

	mesglen = cmdlen = BUFSIZ;
	sock_id = make_client_socket_dgram();
	make_server_address(&saddr,SERVER,SERVER_PORT);
	apply_permit_to_run(sock_id,saddr,mesg,&mesglen);
	client_handler(sock_id,&saddr,mesg,cmd);
	while(1)
	{
		receive_from_server(sock_id,&saddr,cmd,&cmdlen);
		client_handler(sock_id,&saddr,cmd,mesg);
	}
	close(sock_id);
}
