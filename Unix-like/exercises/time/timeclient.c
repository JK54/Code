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
	/* char *hostname = "jk54.tpddns.cn"; */
	char *hostname = "192.168.1.2";
	char *serv = "13";

	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;

	getaddrinfo(hostname,serv,&hint,&res);
	if(connect(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("connect");
	while(read(sock_id,message,BUFSIZ) > 0)
	{
		printf("%s",message);
		memset(message,'\0',strlen(message));
	}
	close(sock_id);
	freeaddrinfo(res);
}
