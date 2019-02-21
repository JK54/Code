#include <stdlib.h>

int builtin_command(char **,int *);
int  main_process();
char *next_cmd();
char **splitline(char *,int *,int *);
void freelist(char **);
void *emalloc(size_t);
void *erealloc(void *,size_t);
int process(char **,int);
int execute(char **,int);
void fatal(char *,char *,int);
