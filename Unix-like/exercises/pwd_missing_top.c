#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXSIZE 200

void do_pwd();
char *getcurrentdname();
bool istop();

int main(int argc,char **argv)
{
	do_pwd();
	return 0;
}

void do_pwd()
{
	char path[MAXSIZE] = {};
	char tmp[MAXSIZE] = {};
	while(!istop())
	{
		strncpy(tmp,path,strlen(path));
		snprintf(path,MAXSIZE,"%s%c%s",getcurrentdname(),'/',tmp);
		chdir("..");
	}
	printf("%s\n",path);
}

char *getcurrentdname()
{
	DIR *dir;
	struct stat cursta;
	struct dirent *dirp;
	stat(".",&cursta);
	dir = opendir("..");
	for(dirp = readdir(dir);cursta.st_ino != dirp->d_ino;dirp = readdir(dir));
	closedir(dir);
	return dirp->d_name;
}

bool istop()
{
	struct stat cur,upr;
	stat(".",&cur);
	stat("..",&upr);
	return cur.st_ino == upr.st_ino;
}
