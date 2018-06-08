#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

void show_time(long);
void show_info(struct utmp *);

int main()
{
	struct utmp utbuf;
	int utmpfd;
	if((utmpfd = open(UTMP_FILE,O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd,&utbuf,sizeof(utbuf)) == sizeof(utbuf))
		show_info(&utbuf);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s",utbufp->ut_user);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	show_time(utbufp->ut_tv.tv_sec);
	printf(" ");
	printf("%-s",utbufp->ut_host);
	printf("\n");
}

void show_time(long timeval)
{
	char *cp;
	cp = ctime(&timeval);
	printf("%12.12s",cp);
}
