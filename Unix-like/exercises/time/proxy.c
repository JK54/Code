#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <strings.h>
#include <string.h>
#include <signal.h>

#define TIMELISTENPORT "13"
#define TIMESERVERPORT "13194"
#define PROXYPORT "13193"
#define HOSTLEN 256
#define MAXIPNUM 500
#define TIMESERVER "127.0.0.1"
#define oops(msg){perror(msg);exit(EXIT_FAILURE);}

static char iplist[MAXIPNUM][INET_ADDRSTRLEN];
static int ipnum = 0;
static int sock_fd;

void get_allow_ip()
{
	FILE *fp;
	int col = 0,row = 0;
	char *tmp = NULL;
	size_t len = INET_ADDRSTRLEN;
	fp = fopen("./allow_ip_list.dat","r");
	while(getline(&tmp,&len,fp) != -1)
		strncpy(iplist[ipnum++],tmp,strlen(tmp));
	free(tmp);
}

bool is_allowed(char *ip)
{
	size_t len = strlen(ip);
	int i;
	for(i = 0;i < ipnum;i++)
		if(strncmp(ip,iplist[i],len) == 0)
			break;
	if(i < ipnum)
		return true;
	return false;
}

void sighandler(int signum)
{
	if(signum == SIGINT)
	{
		char str2[] = "shut down by server\n";
		write(sock_fd,str2,strlen(str2));
		shutdown(sock_fd,SHUT_RDWR);
		printf("shut down");
		exit(signum);
	}
}


int main(int argc,char **argv)
{
	char hostname[HOSTLEN];
	char str0[INET_ADDRSTRLEN];
	char str1[] = "you are not allowed to connect the server.\n";
	char buffer[BUFSIZ];
	int sock_to_time_server,sock_rev_from_client;
	int addr_no;
	struct addrinfo hint,*res_server,*res_client;
	struct sockaddr_in client;
	socklen_t addrlen = sizeof(client);

	get_allow_ip();
	signal(SIGINT,sighandler);

	sock_rev_from_client = socket(PF_INET,SOCK_STREAM,0);
	if(sock_rev_from_client == -1)
		oops("socket");
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_flags = AI_PASSIVE;
	hint.ai_socktype = SOCK_STREAM;
	snprintf(hostname,HOSTLEN,"%d",INADDR_ANY);
	addr_no = getaddrinfo(hostname,TIMELISTENPORT,&hint,&res_client);
	if(addr_no != 0)
	{
		fprintf(stderr,"cannot get information for " "%s : error:%s\n",hostname,gai_strerror(addr_no));
		exit(1);
	}
	if(bind(sock_rev_from_client,res_client->ai_addr,sizeof(struct sockaddr)) != 0)
		oops("bind");
	if(listen(sock_rev_from_client,1) == -1)
		oops("listen");

	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	addr_no = getaddrinfo(TIMESERVER,TIMESERVERPORT,&hint,&res_server);
	if(addr_no != 0)
	{
		fprintf(stderr,"cannot get information for " "%s : error:%s\n",TIMESERVER,gai_strerror(addr_no));
		exit(1);
	}	
	
	while(1)
	{
		sock_fd = accept(sock_rev_from_client,(struct sockaddr *)&client,&addrlen);
		if(sock_fd == -1)
			oops("accpet");
		printf("get a call from %s\n",inet_ntop(AF_INET,&client.sin_addr,str0,sizeof(str0)));
		if(is_allowed(str0))
		{
			if((sock_to_time_server = socket(AF_INET,SOCK_STREAM,0)) == -1)
				oops("socket");
			if(connect(sock_to_time_server,res_server->ai_addr,sizeof(struct sockaddr)) != 0)
				oops("connect");
			while(read(sock_to_time_server,buffer,BUFSIZ) > 0)
				write(sock_fd,buffer,strlen(buffer));
			shutdown(sock_to_time_server,SHUT_RDWR);
			close(sock_to_time_server);
		}
		else
			write(sock_fd,str1,strlen(str1));
		shutdown(sock_fd,SHUT_WR);
	}
	return 0;
}
