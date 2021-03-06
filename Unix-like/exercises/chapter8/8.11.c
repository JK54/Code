#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define MAXARGS 20
#define ARGLEN 100

int main()
{
	char *arglist[MAXARGS + 1];
	char *ex = "exit";
	int numargs;
	char argbuf[ARGLEN];
	char * makestring();
	int execute();
	numargs = 0;
	while(numargs < MAXARGS)
	{
		printf("Arg[%d]?",numargs);
		if(fgets(argbuf,ARGLEN,stdin) && *argbuf != '\n' && strncmp(argbuf,ex,4) != 0)
			arglist[numargs++] = makestring(argbuf);
		else if(strncmp(argbuf,ex,4) == 0)
			exit(0);
		else
		{
			if(numargs > 0)
			{
				arglist[numargs] = NULL;
				execute(arglist);
				numargs = 0;
			}
		}
	}
	return 0;
}

int execute(char *arglist[])
{
	int pid,exitstatus;
	pid = fork();
	switch(pid)
	{
		case -1:
			perror("fork failed..");
			exit(1);
		case 0:
			execvp(arglist[0],arglist);
			perror("execvp failed..");
			exit(1);
		default:
			while(wait(&exitstatus) != pid);
			printf("child exited with status %d,%d\n",exitstatus >> 8,exitstatus & 0377);
			return 0;
	}
}

char *makestring(char *buf)
{
	char *cp;
	buf[strlen(buf) - 1] = '\0';
	cp = malloc(strlen(buf) + 1);
	if(cp == NULL)
	{
		fprintf(stderr,"no memory\n");
		exit(1);
	}
	strncpy(cp,buf,strlen(buf));
	return cp;
}
