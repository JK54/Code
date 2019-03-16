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
#define oops(msg){perror(msg);exit(EXIT_FAILURE);}

int main(int argc,char **argv)
{
	struct addrinfo hint,*res;
	char hostname[HOSTLEN];
	int sock_id,sock_fd;
	int addr_no;
	char serv[HOSTLEN],*ctime();
	time_t thetime;

	sock_id = socket(AF_INET,SOCK_STREAM,0);
	if(sock_id == -1)
		oops("socket");

	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_flags = AI_PASSIVE;
	hint.ai_socktype = SOCK_STREAM; 
	snprintf(serv,HOSTLEN,"%d",PORTNUM);
	snprintf(hostname,HOSTLEN,"%d",INADDR_ANY);
	if((addr_no = getaddrinfo(hostname,serv,&hint,&res)) != 0)
	{
		fprintf(stderr,"cannot get information for " "%s : error:%s\n",hostname,gai_strerror(addr_no));
		exit(EXIT_FAILURE);
	}
	if(bind(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("bind");
	if(listen(sock_id,2) != 0)
		oops("listen");

	while(1)
	{
		sock_fd = accept(sock_id,NULL,NULL);
		if(sock_fd == -1)
			oops("accpet");
		thetime = time(NULL);
		write(sock_fd,"the time here is ",sizeof("the time here is "));
		write(sock_fd,ctime(&thetime),strlen(ctime(&thetime)));
		shutdown(sock_fd,SHUT_RDWR);
	}
	freeaddrinfo(res);
	return 0;
}
