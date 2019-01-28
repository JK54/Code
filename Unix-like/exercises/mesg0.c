#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <utmp.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFCOUNT 16

void get_tty(char *ttyname);

int main(int ac,char **av)
{
	char tty[20];
	if (ac != 2)
	{
		perror("usage : mesg0 option(n/y)");
		exit(1);
	}
	get_tty(tty);
	if(av[1][0] == 'y')
		chmod(tty,S_IRUSR | S_IWUSR | S_IWGRP);
	else if(av[1][0] == 'n')
		chmod(tty,S_IRUSR | S_IWUSR);
	else
	{
		perror("invalid option");
		exit(1);
	}
	return 0;
}

void get_tty(char *ttyname)
{
	struct utmp user[BUFFCOUNT];
	struct passwd *pbuf;
	uid_t id;
	FILE *file;
	file = fopen(UTMP_FILE,"r");
	id = geteuid();
	pbuf = getpwuid(id);
	while(fread(user,sizeof(struct utmp),BUFFCOUNT,file) > 0)
		for(int i = 0;i < BUFFCOUNT;i++)
			if(user[i].ut_type == USER_PROCESS)
				if(strncmp(user[i].ut_user,pbuf->pw_name,strlen(pbuf->pw_name)) == 0)
				{
					if(user[i].ut_line[0] == ':')
						snprintf(ttyname,BUFFCOUNT,"%s%c","/dev/pts/",user[i].ut_line[1]);
					else
						snprintf(ttyname,BUFFCOUNT,"%s",user[i].ut_line);
					break;
				}
	fclose(file);
}
