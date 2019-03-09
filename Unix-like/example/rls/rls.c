#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define oops(m){perror(m);exit(EXIT_FAILURE);}
#define PORTNUM 13194

int main(int argc,char **argv)
{
	struct addrinfo hint,*res;
	int sock_id,sock_fd;
	int addr_no;
	char buffer[BUFSIZ],serv[BUFSIZ];
	int n_read;
	
	if(argc != 3)
	{
		printf("usage : rls hostname dirname\n");
		exit(EXIT_FAILURE);
	}
	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	snprintf(serv,BUFSIZ,"%d",PORTNUM);
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	if((addr_no = getaddrinfo(argv[1],serv,&hint,&res)) != 0)
	{
		fprintf(stderr,"cannot get information for " "%s : error:%s\n",argv[1],gai_strerror(addr_no));
		exit(EXIT_FAILURE);
	}
	if(connect(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("connect");
	if(write(sock_id,argv[2],strlen(argv[2])) == -1)
		oops("write");
	if(write(sock_id,"\n",1) == -1)
		oops("write");
	while((n_read = read(sock_id,buffer,BUFSIZ)) != 0)
		if(write(fileno(stdout),buffer,n_read) == -1)
		/* if(write(1,buffer,n_read) == -1) */
			oops("write");
	close(sock_id);
}
