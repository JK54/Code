#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#include <stdlib.h>
#define PORTNUM 13000
#define HOSTLEN 256
#define oops(msg){perror(msg);exit(1);}

int main(int argc,char **argv)
{
	struct sockaddr_in saddr;
	struct hostent *hp;
	char hostname[HOSTLEN];
	int sock_in,sock_fd;
	FILE *sock_fp;
	char *ctime();
	time_t thetime;
}
