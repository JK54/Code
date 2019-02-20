#include "smsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* next_cmd(char* prompt, FILE* fp)
{
    char* buf;
    int bufspace = 0;
    int pos = 0;
    int c;

    printf("%s", prompt);
    while ((c = getc(fp)) != EOF) 
	{
		if (pos + 1 >= bufspace) 
		{
		    if(bufspace == 0)
				buf = emalloc(BUFSIZ);
		    else
				buf = erealloc(buf, bufspace + BUFSIZ);
			bufspace += BUFSIZ;
		}
		if (c == '\n')
		    break;
		buf[pos++] = c;
    }
    if (c == EOF && pos == 0)
		return NULL;
    buf[pos] = '\0';
    return buf;
}

#define is_delim(x) ((x) == ' ' || (x) == '\t')
#define is_reg(x) ((x) != ';' && (x) != '&' && (x) != '\0')

char** splitline(char *line, int *cmdapartpos,int *argnum)
{
    char* newstr();
    char** args;
    int spots;
    int bufspace;
    int row;
    char* cp;
    int start,pos;

    if (line == NULL)
		return NULL;

    args = emalloc(BUFSIZ);
    spots = BUFSIZ / sizeof(char*);
    bufspace = BUFSIZ;
    pos = *cmdapartpos;
	row = 0;
	cp = line;
	while(is_reg(cp[pos]))
	{
		while(is_delim(cp[pos]))
			pos++;
		if(!is_reg(cp[pos]))
			break;
		for(start = pos;!is_delim(cp[pos]) && is_reg(cp[pos]);pos++);
		if(row + 1 >= spots)
		{
			bufspace += BUFSIZ;
			args = erealloc(args,bufspace);
			spots += BUFSIZ / sizeof(char*);
		}
		args[row++] = newstr(cp,start,pos - start);
	}
	if(cp[pos] == ';')
		pos++;
	else if(cp[pos] == '&')
		args[row++] = newstr(cp,pos++,1);
    args[row] = NULL;
	*cmdapartpos = pos;
	*argnum = row;
    return args;
}

char* newstr(char* s, int start, int len)
{
    char* rv = emalloc(len + 1);
    rv[len] = '\0';
    strncpy(rv, s + start, len);
    return rv;
}

void freelist(char** list)
{
    char** cp = list;
    while (*cp)
		free(*cp++);
    free(list);
}

void* emalloc(size_t n)
{
    void* rv;
    if ((rv = malloc(n)) == NULL)
		fatal("out of memory", "", 1);
    return rv;
}

void* erealloc(void* p, size_t n)
{
    void* rv;
    if ((rv = realloc(p, n)) == NULL)
		fatal("realloc() failed", "", 1);
	return rv;
}
