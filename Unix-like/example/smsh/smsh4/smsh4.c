#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "smsh.h"
#include "macro.h"
#include "varlib.h"

#define DEFAULT_PROMPT "> "

void setup();
char ** environ;

int main()
{
	int res = 0;
	setup();
	while(res != END_NO)
		res = main_process();
	if(environ != NULL)
		freelist(environ);
	return res;
}

void setup()
{
	VLenviron2table(environ);
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
}

void fatal(char *s1,char *s2,int n)
{
	fprintf(stderr,"Error:%s,%s\n",s1,s2);
	exit(n);
}

int main_process()
{
	char *cmdline;
	char *prompt = DEFAULT_PROMPT;
	int cmdlen,cmdapartpos,argnum;
	int result = END_NO;
	char **arglist;
	if((cmdline = next_cmd(prompt,stdin)) != NULL)
	{
		cmdlen = strlen(cmdline);
		cmdapartpos = 0;
		do
		{
			arglist = splitline(cmdline,&cmdapartpos,&argnum);
			result = process(arglist,argnum);
			freelist(arglist);
		}while(cmdapartpos < cmdlen);
		free(cmdline);
	}
	return result;
}
