#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int execute(char *argv[],int argnum)
{
	int pid;
	int child_info = -1;
	if(argnum == 0)
		return 0;
	if(strncmp(argv[0],"exit",4) == 0)
	{
		if(argnum == 1)
			exit(0);
		else
			exit(atoi(argv[1]));
	}
	if((pid = fork()) == -1)
		perror("fork");
	else if(pid == 0)
	{
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT,SIG_DFL);
		if(strncmp(argv[argnum - 1],"&",1) == 0)
		{
			if(daemon(1,1) != 0)
				perror("daemon init");
			argv[argnum - 1] = NULL;
		}
		execvp(argv[0],argv);
		perror("cannot execute command");
		exit(1);
	}
	else
	{
		if(wait(&child_info) == -1)
			perror("wait");
		if(strncmp(argv[argnum - 1],"&",1) == 0)
			printf("[1]%d\tDone\t\t%s\n",pid,argv[0]);
	}
	return child_info;
}
