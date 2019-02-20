#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "smsh.h"

#define DEFAULT_PROMPT "> "

int main()
{
	char *cmdline,*prompt,**arglist;
	int result;
	int cmdlen,cmdapartpos,argnum;

	void setup();
	prompt = DEFAULT_PROMPT;
	setup();
	while((cmdline = next_cmd(prompt,stdin)) != NULL)
	{
		cmdlen = strlen(cmdline);
		cmdapartpos = 0;
		do
		{
			arglist = splitline(cmdline,&cmdapartpos,&argnum);
			result = execute(arglist,argnum);
			freelist(arglist);
		}while(cmdapartpos < cmdlen);
		free(cmdline);
	}
	return 0;
}

void setup()
{
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
}

void fatal(char *s1,char *s2,int n)
{
	fprintf(stderr,"Error:%s,%s\n",s1,s2);
	exit(n);
}
