#include <stdio.h>
#include <string.h>
#include "smsh.h"
#include "macro.h"
#include "varlib.h"

#define MAXRECDEEP 20

enum states {NEUTRAL,IF_SUCCEEDED,IF_FAILED,SKIPPING_THEN,DOING_THEN,SKIPPING_ELSE,DOING_ELSE};
static int if_state = NEUTRAL;

struct stack
{
	int if_state;
};

static struct stack if_stack[MAXRECDEEP];
static int recdeep = 0;

char *states2str(int state)
{
	switch(state)
	{
		case NEUTRAL:
			return "NEUTRAL";
		case IF_SUCCEEDED:
			return "IF_SUCCEEDED";
		case IF_FAILED:
			return "IF_FAILED";
		case SKIPPING_THEN:
			return "SKIPPING_THEN";
		case DOING_THEN:
			return "DOING_THEN";
		case SKIPPING_ELSE:
			return "SKIPPING_ELSE";
		case DOING_ELSE:
			return "DOING_ELSE";
	}
	return NULL;
}

int syn_err(char *msg)
{
	if_state = NEUTRAL;
	fprintf(stderr,"syntax error : %s\n",msg);
	return SYNTAX_ERRNO;
}

int ok_to_execute()
{
	int rv = FALSE;
	if(if_state == SKIPPING_THEN || if_state == SKIPPING_ELSE || if_state == IF_FAILED || if_state == IF_SUCCEEDED)
		rv = FALSE;
	else if(if_state == NEUTRAL || if_state == DOING_THEN || if_state == DOING_ELSE)
		rv = TRUE;
	return rv;
}

int is_control_command(char *s)
{
	return get_keyword_no(s);
}

int do_control_command(char **args,int argnum,int keyno)
{
	char *cmd = args[0];
	int rv = END_NO;

	if(keyno >= IF && keyno <= FI)
	{
		switch(keyno)
		{
			case IF:
				if(if_state == IF_SUCCEEDED || if_state == IF_FAILED)
					rv = syn_err("if unexpected");
				else if(if_state == SKIPPING_THEN || if_state == SKIPPING_ELSE)
					rv = SUCCESS;
				else
				{
					if(if_state != NEUTRAL)
						if_stack[recdeep++].if_state = if_state;
					if(argnum > 1)
						rv = process(args + 1,argnum - 1);
					else
						rv = main_process();
					if(rv == SUCCESS)
						if_state = IF_SUCCEEDED;
					else
						if_state = IF_FAILED;
				}
				break;
			case THEN:
				if(if_state == IF_FAILED)
				{
					if_state = SKIPPING_THEN;
					rv = SUCCESS;
				}
				else if(if_state == IF_SUCCEEDED)
				{
					if_state = DOING_THEN;
					if(argnum > 1)
						rv = process(args + 1,argnum - 1);
					else
						rv = main_process();
				}	
				else
					rv = syn_err("then unexpected");
				break;
			case ELSE:
				if(if_state == SKIPPING_THEN)
				{
					if_state = DOING_ELSE;
					rv = SUCCESS;
				}
				else if(if_state == DOING_THEN)
				{
					if_state = SKIPPING_ELSE;
					if(argnum > 1)
						rv = process(args + 1,argnum - 1);
					else
						rv = main_process();
				}	
				else
					rv = syn_err("else unexpected");
				break;
			case FI:
				{
					if(if_state == NEUTRAL || if_state == IF_FAILED || if_state == IF_SUCCEEDED)
						rv = syn_err("fi unexpected");
					else if(recdeep == 0)
					{
						printf("if-statement succeed\n");
						if_state = NEUTRAL;
						rv = SUCCESS;
					}
					else
					{
						if_state = if_stack[--recdeep].if_state;
						rv = SUCCESS;
					}
				}
				break;
			default:
				fatal("internal error processing:",cmd,2);
		}
		if_stack[recdeep].if_state = if_state;
	}
	else if(keyno >= FOR && keyno <= DONE)
	{
		
	}
	return rv;
}
