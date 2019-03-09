#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <time.h>
#include <strings.h>
#include <string.h>

#define PORTNUM 13194
#define HOSTLEN 256
#define oops(msg){perror(msg);exit(1);}

int main(int argc,char **argv)
{
	struct sockaddr_in saddr;
	struct hostent *hp;
	char hostname[HOSTLEN];
	int sock_id,sock_fd;
	FILE *sock_fp;
	char *ctime();
	time_t thetime;

	sock_id = socket(PF_INET,SOCK_STREAM,0);
	if(sock_id == -1)
		oops("socket");

	bzero((void *) &saddr,sizeof(saddr));
	gethostname(hostname,HOSTLEN);
	hp = gethostbyname(hostname);
	bcopy((void *)hp->h_addr_list,(void *)&saddr.sin_addr,hp->h_length);
	saddr.sin_port = PORTNUM;
	saddr.sin_family = AF_INET;
	if(bind(sock_id,(struct sockaddr *) &saddr,sizeof(struct sockaddr)) != 0)
		oops("bind");

	if(listen(sock_id,1) != 0)
		oops("listen");

	while(1)
	{
		sock_fd = accept(sock_id,NULL,NULL);
		printf("get a call\n");
		if(sock_fd == -1)
			oops("accpet");
		sock_fp = fdopen(sock_fd,"w");
		if(sock_fp == NULL)
			oops("fdopen");
		thetime = time(NULL);
		fprintf(sock_fp,"the time here is");
		fprintf(sock_fp,"%s",ctime(&thetime));
		fclose(sock_fp);
	}
	return 0;
}
