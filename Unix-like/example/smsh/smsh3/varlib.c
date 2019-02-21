#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varlib.h"
#include "macro.h"

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
	
	if((itemp = find_item(name,1)) != NULL && (s = new_string(name,val)) != NULL)
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

	if((itemp = find_item(name,0)) != NULL)
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
	if((itemp = find_item(name,0)) != NULL)
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
