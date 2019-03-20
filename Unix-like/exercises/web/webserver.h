#include "socklib.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <ctype.h>

void read_request(int fd,char *buffer,int size);
char* newstr(char *source,int spos,int epos);
char** split_args(char *buf);
void freelist(char **buf);
void do_cat(int fd,char *filename);
bool is_exist(char *name);
void error_404(int fd,char *item);
bool is_dir(char *name);
void do_ls(int fd,char *dirname);
bool is_cgi(char *name);
void do_exec(int fd,char *prog);
void error_501(int fd);
