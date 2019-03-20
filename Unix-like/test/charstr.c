#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* newstr(char *source,int spos,int epos)
{
    char *res = malloc(epos - spos + 1);
    strncpy(res,source,epos - spos);
    return res;
}


int main()
{
	char *a = newstr("ls",0,3);
	printf("%s\n",a);
	free(a);
}
