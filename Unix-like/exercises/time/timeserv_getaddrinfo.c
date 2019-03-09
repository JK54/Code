#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <strings.h>
#include <string.h>

#define PORTNUM 13194
#define HOSTLEN 256
#define oops(msg){perror(msg);exit(1);}

int main(int argc,char **argv)
{
	struct addrinfo hint,*res;
	char hostname[HOSTLEN];
	int sock_id,sock_fd;
	int addr_no;
	FILE *sock_fp;
	char serv[HOSTLEN],*ctime();
	time_t thetime;

	sock_id = socket(PF_INET,SOCK_STREAM,0);
	if(sock_id == -1)
		oops("socket");

	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_flags = AI_PASSIVE;
	hint.ai_socktype = SOCK_STREAM; 
	/* gethostname(hostname,HOSTLEN); */
	snprintf(serv,HOSTLEN,"%d",PORTNUM);
	if((addr_no = getaddrinfo(NULL,serv,&hint,&res)) != 0)
	{
		fprintf(stderr,"cannot get information for " "%s : error:%s\n",hostname,gai_strerror(addr_no));
		exit(1);
	}
	if(bind(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("bind");

	if(listen(sock_id,1) != 0)
		oops("listen");

	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		char str[INET_ADDRSTRLEN];
		sock_fd = accept(sock_id,(struct sockaddr *)&client,&len);
		printf("get a call form %s\n",inet_ntop(AF_INET,&client.sin_addr,str,sizeof(str)));
		if(sock_fd == -1)
			oops("accpet");
		sock_fp = fdopen(sock_fd,"w");
		if(sock_fp == NULL)
			oops("fdopen");
		thetime = time(NULL);
		fprintf(sock_fp,"the time here is");
		fprintf(sock_fp,"%s",ctime(&thetime));
		fclose(sock_fp);
	}
	freeaddrinfo(res);
	return 0;
}
