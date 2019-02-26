#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varlib.h"
#include "macro.h"

#define MAXVARS 200

#define RETURN_BLANK_POS 1
#define IGNORE_BLANK_POS 0

#define MAXKEYLEN 5
#define MINKEYLEN 2
static char *keyword[] = {"if","then","else","fi","for","in","do","done","while"};

struct var
{
	char *str;
	int global;
};

static struct var tab[MAXVARS];
static char* new_string(char *name,char *val);
static struct var* find_item(char *,int);

int VLstore(char *name,char *val)
{
	struct var *itemp;
	char *s;
	int rv = 1;
	
	if((itemp = find_item(name,RETURN_BLANK_POS)) != NULL && (s = new_string(name,val)) != NULL)
	{
		if(itemp->str != NULL)
			free(itemp->str);
		itemp->str = s;
		rv = 0;
	}
	return rv;
}

char* VLlookup(char *name)
{
	struct var *itemp;

	if((itemp = find_item(name,IGNORE_BLANK_POS)) != NULL)
		return itemp->str + 1 + strlen(name);
	return "";
}

void VLlist()
{
	int i;
	for(i = 0;i < MAXVARS && tab[i].str != NULL;i++)
	{
		if(tab[i].global)
			printf(" * %s\n",tab[i].str);
		else
			printf(" %s\n",tab[i].str);
	}
}

int VLexport(char *name)
{
	struct var *itemp;
	int rv = 1;
	if((itemp = find_item(name,IGNORE_BLANK_POS)) != NULL)
	{
		itemp->global = 1;
		rv = 0;
	}
	else if(VLstore(name,"") == 1)
		rv = VLexport(name);
	return rv;
}

char* new_string(char *name,char *val)
{
	char *retval;
	retval = malloc(strlen(name) + strlen(val) + 2);
	if(retval != NULL)
		snprintf(retval,strlen(name) + 2 + strlen(val),"%s=%s",name,val);
	return retval;
}

static struct var* find_item(char *name,int first_blank)
{
	int i;
	int len = strlen(name);
	char *s;
	for(i = 0;i < MAXVARS && tab[i].str != NULL;i++)
	{
		s = tab[i].str;
		if(strncmp(s,name,len) == 0 && s[len] == '=')
			return &tab[i];
	}
	if(i < MAXVARS && first_blank)
		return &tab[i];
	return NULL;
}

int VLenviron2table(char *env[])
{
	if(env == NULL)
		return TRUE;
	int i;
	char *newstring;

	for(i = 0;env[i] != NULL;i++)
	{
		if(i == MAXVARS)
			return FALSE;
		newstring = malloc(1 + strlen(env[i]));
		if(newstring == NULL)
			return FALSE;
		strncpy(newstring,env[i],strlen(env[i]));
		tab[i].str = newstring;
		tab[i].global = 1;
	}
	while(i < MAXVARS)
	{
		tab[i].str = NULL;
		tab[i++].global = 1;
	}
	return TRUE;
}

char** VLtable2environ()
{
	int i,j,n = 0;
	char **envtab;
	for(i = 0;i < MAXVARS && tab[i].str != NULL;i++)
	{
		if(tab[i].global == 1)
			n++;
	}
	envtab = (char **)malloc((n + 1) * sizeof(char *));
	if(envtab == NULL)
		return NULL;
	for(i = 0,j = 0;i < MAXVARS && tab[i].str != NULL;i++)
		if(tab[i].global == 1)
			envtab[j++] = tab[i].str;
	envtab[j] = NULL;
	return envtab;
}

int get_keyword_no(char *s)
{
	int len = strlen(s);
	int size = sizeof(keyword) / sizeof(keyword[0]);
	int i,rv;
	rv = NOT_KEYWORD;
	if(len > MAXKEYLEN || len < MINKEYLEN)
		i = NOT_KEYWORD;
	else
		for(i = IF;i < size;i++)
		{
			if(len == strlen(keyword[i]) && strncmp(s,keyword[i],len) == 0)
			{
				rv = i;
				break;
			}
		}
	return rv;
}
