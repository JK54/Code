#include "smsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* next_cmd(char* prompt, FILE* fp)
{
    char* buf;
    int bufspace = 0;
    int pos = 0;
    int c;

    printf("%s", prompt);
    while ((c = getc(fp)) != EOF) {
	if (pos + 1 >= bufspace) 
	{
	    if (bufspace == 0)
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

char** splitline(char* line, int* cmdapartpos)
{
    char* newstr();
    char** args;
    int spots = 0;
    int bufspace = 0;
    int argnum = 0;
    char* cp = line;
    int start, len, pos;

    if (line == NULL)
	return NULL;

    args = emalloc(BUFSIZ);
    bufspace = BUFSIZ;
    spots = BUFSIZ / sizeof(char*);
    pos = *cmdapartpos;
	
    while (cp[pos] != '\0' && cp[pos] != ';') 
	{
		while (is_delim(cp[pos]))
	    	pos++;
		if (cp[pos] == '\0' || cp[pos] == ';')
	    	break;
		if (argnum + 1 >= spots) 
		{
			args = erealloc(args, bufspace + BUFSIZ);
	   	 	bufspace += BUFSIZ;
	   	 	spots += BUFSIZ / sizeof(char*);
		}
		start = pos;
		len = 1;
		while (cp[++pos] != '\0' && !is_delim(cp[pos]) && cp[pos] != ';')
		    len++;
		args[argnum++] = newstr(cp, start, len);
    }
    args[argnum] = NULL;
    *cmdapartpos = pos;
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