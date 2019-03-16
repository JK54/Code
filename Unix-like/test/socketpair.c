#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define oops(m){perror(m);exit(1);}

int main(int argc,char **argv)
{
	int p[2];
	int pid;
	if(argc != 2)
	{
		printf("usage : sockpair pathname\n");
		exit(1);
	}
	if(socketpair(AF_UNIX,SOCK_STREAM,PF_UNSPEC,p) == -1)
		oops("pipe");
	if((pid = fork()) == -1)
		oops("fork");
	if(pid == 0)
	{
		char buf[BUFSIZ];
		close(p[0]);
		dup2(p[1],STDIN_FILENO);
		dup2(p[1],STDOUT_FILENO);
		close(p[1]);
		execlp("ls","ls","--color=auto",argv[1],NULL);
	}
	else
	{
		char buf[BUFSIZ];
		close(p[1]);
		/* wait(NULL); */
		while(read(p[0],buf,BUFSIZ) != 0)
			printf("%s",buf);	
		shutdown(p[0],SHUT_WR);
		close(p[0]);
		wait(NULL);
	}
}
