#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <utmp.h>
#include <sys/types.h>

#define BUFFCOUNT 16

void get_tty_by_name(char *name,char *ttyname);

int main(int ac,char **av)
{
	FILE *fd;
	char tty[BUFFCOUNT],buf[BUFSIZ];
	if(ac != 2)
	{
		fprintf(stderr,"usage: write2 username\n");
		exit(1);
	}
	get_tty_by_name(av[1],tty);
	printf("%s\n",tty);
	fd = fopen(tty,"w");
	if(fd == NULL)
	{
		perror(tty);
		exit(1);
	}
	while(fgets(buf,BUFSIZ,stdin) != NULL)
		if(fwrite(buf,sizeof(char),strlen(buf),fd) == 0)
			break;
	fclose(fd);
}

void get_tty_by_name(char *name,char *ttyname)
{
	struct utmp user[BUFFCOUNT];
	FILE *file;
	file = fopen(UTMP_FILE,"r");
	while(fread(user,sizeof(struct utmp),BUFFCOUNT,file) > 0)
		for(int i = 0;i < BUFFCOUNT;i++)
			if(user[i].ut_type == USER_PROCESS)
				if(strncmp(user[i].ut_user,name,strlen(name)) == 0)
				{
					if(user[i].ut_line[0] == ':')
						snprintf(ttyname,BUFFCOUNT,"%s%c","/dev/pts/",user[i].ut_line[1]);
					else
						snprintf(ttyname,BUFFCOUNT,"%s",user[i].ut_line);
					break;
				}
	fclose(file);
}
