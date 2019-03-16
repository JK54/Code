#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <wait.h>
#include <arpa/inet.h>

#define oops(m){perror(m);exit(EXIT_FAILURE);}
#define PORTNUM 13194

int main()
{
	struct addrinfo hint,*res;
	int sock_id;
	int	sock_fd;

	char hostname[BUFSIZ];
	char serv[BUFSIZ];
	char dirname[BUFSIZ];
	char buffer[BUFSIZ];
	
	int gai_no;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	char address[INET_ADDRSTRLEN];

	int pid;
	int pp[2];

	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	snprintf(hostname,BUFSIZ,"%x",INADDR_ANY);
	snprintf(serv,BUFSIZ,"%d",PORTNUM);
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	if((gai_no = getaddrinfo(hostname,serv,&hint,&res)) != 0)
	{
		fprintf(stderr,"cannot get information .error:%s\n",gai_strerror(gai_no));
		exit(EXIT_FAILURE);
	}

	if(bind(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("bind");
	if(listen(sock_id,1) != 0)
		oops("listen");

	while(1)
	{
		if((sock_fd = accept(sock_id,(struct sockaddr *)&addr,&addrlen)) == -1)
			oops("accpet");
		if(socketpair(AF_UNIX,SOCK_STREAM,AF_UNSPEC,pp) == -1)
			oops("socketpair");
		printf("get a call from %s : %d\n",inet_ntop(AF_INET,&addr.sin_addr,address,sizeof(address)),addr.sin_port);
		if(read(sock_fd,dirname,BUFSIZ) == -1)
			oops("read dirname");
		if((pid = fork()) == -1)
			oops("fork");
		if(pid == 0)
		{
			close(sock_fd);
			close(pp[0]);
			if(dup2(pp[1],STDIN_FILENO) == -1 || dup2(pp[1],STDOUT_FILENO) == -1)
				oops("dup");
			close(pp[1]);
			execlp("ls","ls","-ltrh",dirname,NULL);
			oops("execute");
		}
		else
		{
			close(pp[1]);
			while(read(pp[0],buffer,BUFSIZ) != 0)
			{
				write(sock_fd,buffer,strlen(buffer));
				memset(buffer,'\0',strlen(buffer));
			}
			wait(NULL);
			close(pp[0]);
			shutdown(sock_fd,SHUT_RDWR);
			close(sock_fd);
		}
	}
	return 0;
}
