#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define oops(m){perror(m);exit(1);}

int main()
{
	int p[2];
	int pid;
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
		execlp("sort","sort",NULL);
		oops("sort");
	}
	else
	{
		char buf[BUFSIZ];
		close(p[1]);
		while(read(STDIN_FILENO,buf,BUFSIZ) != 0)
			write(p[0],buf,strlen(buf));
		shutdown(p[0],SHUT_WR);
		while(read(p[0],buf,BUFSIZ) != 0)
			printf("%s",buf);
		close(p[0]);
		wait(NULL);
	}
}
