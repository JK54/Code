#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	int p[2];
	if(socketpair(AF_UNIX,SOCK_STREAM,PF_UNSPEC,p) == -1)
		exit(1);
	if(write(p[0],"hello",5) == -1)
		perror("write into pipe[0] failed");
	else
		printf("worked\n");
	return 0;
}
