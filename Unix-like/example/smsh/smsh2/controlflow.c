#include <stdio.h>
#include <string.h>
#include "smsh.h"

enum states {NEUTRAL,WANT_THEN,THEN_BLOCK,ELSE_BLOCK};
enum results {SUCCESS,FAIL};

static int if_state = NEUTRAL;
static int if_result = SUCCESS;
static int last_stat = 0;

int syn_err(char *msg)
{
	if_state = NEUTRAL;
	fprintf(stderr,"syntax error : %s\n",msg);
	return -1;
}

int ok_to_execute()
{
	int rv = 0;
	if(if_state == WANT_THEN)
	{
		syn_err("then expected");
		rv = 0;
	}
	else if((if_state == THEN_BLOCK && if_result == SUCCESS) || (if_state == ELSE_BLOCK && if_result == FAIL) || if_state == NEUTRAL)
		rv = 1;
	return rv;
}

int is_control_command(char *s)
{
	return (strncmp(s,"if",2) == 0 || strncmp(s,"then",4) == 0 || strncmp(s,"else",4) == 0 ||strncmp(s,"fi",2) == 0);
}

int do_control_command(char **args,int argnum)
{
	char *cmd = args[0];
	int rv = -1;
	if(strncmp(cmd,"if",2) == 0)
	{
		if(if_state != NEUTRAL)
			rv = syn_err("if unexpected");
		else
		{
			last_stat = process(args + 1,argnum - 1);
			if_result = (last_stat == 0 ? SUCCESS : FAIL);
			if_state  = WANT_THEN;
			rv = 0;
		}
	}
	else if(strncmp(cmd,"then",4) == 0)
	{
		if(if_state != WANT_THEN)
			rv = syn_err("then unexpected");
		else
		{
			if_state = THEN_BLOCK;
			rv = 0;
		}
	}
	else if(strncmp(cmd,"else",4) == 0)
	{
		if(if_state != THEN_BLOCK)
			rv = syn_err("else unexpected");
		else
		{
			if_state = ELSE_BLOCK;
			rv = 0;
		}
	}
	else if(strncmp(cmd,"fi",2) == 0)
	{
		if(if_state != THEN_BLOCK && if_state != ELSE_BLOCK)
			rv = syn_err("fi unexpected");
		else
		{
			if_state = NEUTRAL;
			rv = 0;
		}
	}
	else
		fatal("internal error processing:",cmd,2);
	return rv;
}
