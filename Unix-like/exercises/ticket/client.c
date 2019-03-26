#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#define oops(m){perror(m);exit(EXIT_FAILURE);}

#define SERVER "192.168.1.2"
#define SERVER_PORT "13194"

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

void chat_with_server(int sock_id,struct sockaddr_in saddr,char *cmd,char *mesg,size_t *mesglen)
{
	struct sockaddr retaddr;
	socklen_t addrlen;
	if(sendto(sock_id,cmd,strlen(cmd),0,(struct sockaddr *)&saddr,sizeof(saddr)) == -1)
		oops("sendto");
	memset(mesg,'\0',*mesglen);
	if(recvfrom(sock_id,mesg,*mesglen,0,&retaddr,&addrlen) == -1)
		oops("receive");
	*mesglen = strlen(mesg);
}

void generate_cmd(char *cmd,char *key)
{
	strncat(cmd," ",strlen(cmd) + 1);
	strncat(cmd,key,strlen(cmd) + strlen(key));
}

void super_sleep()
{
	printf("SuperSleep version 1.0 Running\tLicensed Software\n");
	sleep(5);
	printf("The super sleep program ran as expect.\n");
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
void client_handler(char *mesg)
{
	if(strncmp(mesg,"VALID",5) == 0)
		;
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
	/* char cmd[BUFSIZ] = "VALID"; */
	/* char cmd[BUFSIZ] = "GBYE"; */
	char cmd[BUFSIZ] = "GRANT";
	char key[] = "OS5HG-K90NH-SXOGT-7JYEZ";
	char mesg[BUFSIZ];
	size_t mesglen = BUFSIZ;

	sock_id = make_client_socket_dgram();
	make_server_address(&saddr,SERVER,SERVER_PORT);
	generate_cmd(cmd,key);
	chat_with_server(sock_id,saddr,cmd,mesg,&mesglen);
	client_handler(mesg);
	close(sock_id);
}
