#include <stdio.h>
#include "smsh.h"
#include "macro.h"

int is_control_command(char *);
int do_control_command(char ** args,int argnum,int keyno);
int ok_to_execute();

int process(char **args,int argnum)
{
	int rv,keyno;
	if(args[0] == NULL)
		rv = SUCCESS;
	else if((keyno = is_control_command(args[0])) != NOT_KEYWORD)
		rv = do_control_command(args,argnum,keyno);
	else if(ok_to_execute())
	{
		if(!builtin_command(args,&rv))
			rv = execute(args,argnum);
	}
	else
		rv = FALSE;
	return rv;
}
