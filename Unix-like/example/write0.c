#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096

int main(int ac,char **av)
{
	int fd;
	char buf[BUFSIZE];
	if (ac != 2)
	{
		fprintf(stderr,"usage:write0 ttyname\n");
		exit(1);
	}
	fd = open(av[1],O_WRONLY);
	if(fd == -1)
	{
		perror(av[1]);
		exit(1);
	}
	while(fgets(buf,BUFSIZE,stdin) != NULL)
		if(write(fd,buf,strlen(buf)) == -1)
			break;
	close(fd);
	return 0;
}
