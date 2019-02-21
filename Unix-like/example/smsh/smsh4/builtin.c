#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "smsh.h"
#include "varlib.h"
#include "macro.h"
int assign(char *);
int okname(char *);

int builtin_command(char **args,int *resultp)
{
	int rv = 0;

	if(strncmp(args[0],"set",3) == 0)
	{
		VLlist();
		*resultp = 0;
		rv = 1;
	}
	else if(strchr(args[0],'=') != NULL)
	{
		*resultp = assign(args[0]);
		if(*resultp != VAR_ERRNO)
			rv = 1;
	}
	else if(strncmp(args[0],"export",6) == 0)
	{
		if(args[1] != NULL && okname(args[1]))
			*resultp = VLexport(args[1]);
		else
			*resultp = 1;
		rv = 1;
	}
	else if(strncmp(args[0],"exit",4) == 0)
	{
		if(args[1] != NULL)
			exit(atoi(args[1]));
		else
			exit(0);
	}
	return rv;
}

int assign(char *str)
{
	char *cp;
	int rv;

	cp = strchr(str,'=');
	*cp = '\0';
	if(okname(str))
		rv = VLstore(str,cp + 1);
	else
		rv = VAR_ERRNO;
	*cp = '=';
	return rv;
}

int okname(char *str)
{
	char *cp;

	for(cp = str;*cp != '\0';cp++)
	{
		if((isdigit(*cp) && cp == str) || !(isalnum(*cp) || *cp == '_'))
			return 0;
	}

	return (cp != str);
}
