#include <stdlib.h>
#define YES 1
#define NO  0

char *next_cmd();
char **splitline(char *,int *,int *);
void freelist(char **);
void *emalloc(size_t);
void *erealloc(void *,size_t);
int execute(char **,int);
void fatal(char *,char *,int);
