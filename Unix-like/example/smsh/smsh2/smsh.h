#include <stdlib.h>
#define YES 1
#define NO  0
#define SYNTAX_ERRNO -1
#define END -2
#define DEFAULT_PROMPT "> "

int  main_process();
char *next_cmd();
char **splitline(char *,int *,int *);
void freelist(char **);
void *emalloc(size_t);
void *erealloc(void *,size_t);
int process(char **,int);
int execute(char **,int);
void fatal(char *,char *,int);
