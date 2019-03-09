#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#define oops(m){perror(m);exit(EXIT_FAILURE);}
#define PORTNUM 13194

void sanitize(char *str)
{
	char *src,*dest;
	for(src = dest = str;*src != '\0';src++)
		if(*src == '/' || isalnum(*src))
			*dest++ = *src;
	*dest = '\0';
}

int main()
{
	struct addrinfo hint,*res;
	int addr_no;
	int sock_id,sock_fd;
	FILE *sock_fpi,*sock_fpo;
	FILE *pipe_fp;
	char dirname[BUFSIZ];
	char command[BUFSIZ];
	char serv[BUFSIZ];
	char buffer[BUFSIZ];
	int c;

	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	snprintf(serv,BUFSIZ,"%d",PORTNUM);
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	if((addr_no = getaddrinfo(NULL,serv,&hint,&res)) != 0)
	{
		fprintf(stderr,"cannot get information .error:%s\n",gai_strerror(addr_no));
		exit(EXIT_FAILURE);
	}
	if(bind(sock_id,res->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("bind");
	if(listen(sock_id,1) != 0)
		oops("listen");
	while(1)
	{
		sock_fd = accept(sock_id,NULL,NULL);
		printf("get a call\n");
		if(sock_fd == -1)
			oops("accpet");
		if((sock_fpi = fdopen(sock_fd,"r")) == NULL)
			oops("fdopen reading");
		if(fgets(dirname,BUFSIZ,sock_fpi) == NULL)
			oops("reading dirname");
		sanitize(dirname);
		if((sock_fpo = fdopen(sock_fd,"w")) == NULL)
			oops("fdopen writing");
		snprintf(command,strlen(dirname) + 5,"ls %s",dirname);
		if((pipe_fp = popen(command,"r")) == NULL)
			oops("popen");
		while((fread(buffer,sizeof(char),BUFSIZ,pipe_fp)) != 0)
		{
			fwrite(buffer,sizeof(char),strlen(buffer),sock_fpo);
			fflush(sock_fpo);
			memset(buffer,'\0',strlen(buffer));
		}
		pclose(pipe_fp);
		fclose(sock_fpi);
		fclose(sock_fpo);
	}
	return 0;
}
