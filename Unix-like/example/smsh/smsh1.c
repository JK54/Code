#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "smsh.h"

#define DEFAULT_PROMPT "> "

int main()
{
	char *cmdline,*prompt,**arglist;
	int result;
	int cmdapartpos;
	void setup();
	prompt = DEFAULT_PROMPT;
	setup();
	while((cmdline = next_cmd(prompt,stdin)) != NULL)
	{
		cmdapartpos = 0;
		while((arglist = splitline(cmdline,&cmdapartpos)) != NULL)
		{
			result = execute(arglist);
			freelist(arglist);
		}
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
