#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define oops(m){perror(m);exit(1);}

int main(int argc,char **argv)
{
	struct addrinfo hint,*res;
	int sock_id,sock_fd;
	int addr_no;
	int messlen;
	char message[BUFSIZ];

	if(argc != 3)
	{
		printf("usage:timeclient hostname portnum\n");
		exit(1);
	}
	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	getaddrinfo(argv[1],argv[2],&hint,&res);
	if(connect(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("connect");
	messlen = read(sock_id,message,BUFSIZ);
	if(messlen == -1)
		oops("read");
	if(write(1,message,messlen) != messlen)
		oops("write");
	close(sock_id);
}
