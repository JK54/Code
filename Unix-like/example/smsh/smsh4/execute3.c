#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "varlib.h"
#include "macro.h"
#include <sys/wait.h>

extern char ** environ;

int execute(char *argv[],int argnum)
{
	int pid;
	int child_info = -1;
	if(argnum == 0)
		return 0;
	if((pid = fork()) == -1)
		perror("fork");
	else if(pid == 0)
	{
		environ = VLtable2environ();
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT,SIG_DFL);
		if(strncmp(argv[argnum - 1],"&",1) == 0)
		{
			if(daemon(1,1) != 0)
				perror("daemon init");
			argv[--argnum] = NULL;
		}
		for(int i = 0;i < argnum;i++)
		{
			if(argv[i][0] == VAR_SYMBOL)
			{
				char *tmp = VLlookup(argv[i] + 1);
				strncpy(argv[i],tmp,strlen(tmp));
			}
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
