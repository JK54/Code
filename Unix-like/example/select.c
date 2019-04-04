#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define oops(m,x){perror(m);exit(x);}

void showdata(char *fname,int fd)
{
	char buf[BUFSIZ];
	int n;

	printf("%s:",fname);
	fflush(stdout);
	n = read(fd,buf,BUFSIZ);
	if(n == -1)
		oops(fname,5);
	write(STDOUT_FILENO,buf,n);
	write(STDOUT_FILENO,"\n",1);
}

int main()
{
	int fd1,fd2;
	struct timeval timeout;
	fd_set readfds;
	int maxfd;
	int retval;

	if((fd1 = open("/dev/pts/0",O_RDONLY)) == -1)
		oops("/dev/pts/0",2);
	if((fd2 = open("/dev/pts/1",O_RDONLY)) == -1)
		oops("/dev/pts/0",3);
	maxfd = 1 + (fd1 > fd2 ? fd1 : fd2);
	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(fd1,&readfds);
		FD_SET(fd2,&readfds);
		timeout.tv_sec = 7;
		timeout.tv_usec = 0;
		retval = select(maxfd,&readfds,NULL,NULL,&timeout);
		if(retval == -1)
			oops("retval",4);
		if(retval > 0)
		{
			if(FD_ISSET(fd1,&readfds))
				showdata("/dev/pts/0",fd1);
			if(FD_ISSET(fd2,&readfds))
				showdata("/dev/pts/1",fd2);
		}
		else
			printf("no input.\n");
	}
}
