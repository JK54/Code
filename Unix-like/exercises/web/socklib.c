#include "socklib.h"

int connect_to_server(char *hostname,char *servname)
{
	int sock_id;
	struct addrinfo hint,*res;
	int addr_no;
	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	if((addr_no = getaddrinfo(hostname,servname,&hint,&res)) == -1)
	{
		printf("%s : %s error mesg : %s\n",hostname,servname,gai_strerror(addr_no));
		freeaddrinfo(res);
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);
	if(connect(sock_id,res->ai_addr,sizeof(struct sockaddr)) == -1)
		oops("connect");
	return sock_id;
}

int talk_with_server(FILE *fp)
{
	char buf[BUFSIZ];
	int num = 0,tmp;
	size_t size = sizeof(char);
	while((tmp = fread(buf,size,BUFSIZ,fp)) > 0)
	{
		num += tmp;
		if(fwrite(buf,size,tmp,stdout) == 0)
			oops("talk_with_server : fwrite");
	}
	fflush(fp);
	if(tmp == -1)
		oops("talk_with_server : fread");
	return num;
}

int make_server_socket(char *servname,int backlog)
{
	int sock_id;
	struct addrinfo hint,*res;
	int addr_no;
	char hostname[BUFSIZ];

	if((sock_id = socket(AF_INET,SOCK_STREAM,0)) == -1)
		oops("socket");
	snprintf(hostname,BUFSIZ,"%d",INADDR_ANY);
	memset(&hint,0,sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	if((addr_no = getaddrinfo(hostname,servname,&hint,&res)) == -1)
	{
		printf("%s : %s error mesg : %s\n",hostname,servname,gai_strerror(addr_no));
		freeaddrinfo(res);
		exit(EXIT_FAILURE);
	}
	if(bind(sock_id,res->ai_addr,sizeof(struct sockaddr)) == -1)
	{
		freeaddrinfo(res);
		oops("bind");
	}
	freeaddrinfo(res);
	if(listen(sock_id,backlog) == -1)
		oops("listening");
	return sock_id;
}

int server_accept_socket(int sock_fd,int record)
{
	int fd;
	struct sockaddr client;
	char buf[BUFSIZ];
	socklen_t size = sizeof(client);
	fd = accept(sock_fd,&client,&size);
	if(fd == -1)
		oops("listen");
	memset(buf,'\0',BUFSIZ);
	snprintf(buf,BUFSIZ,"get a call from %s\n",inet_ntoa(((struct sockaddr_in *)&client)->sin_addr));
	write(record,buf,strlen(buf));
	return fd;
}

void process_request_fork(int fd,char *cmd,char **args)
{
	int pid;
	if((pid = fork()) == -1)
		oops("fork");
	if(pid == 0)
	{
		if(dup2(fd,STDOUT_FILENO) == -1 || dup2(fd,STDERR_FILENO) == -1)
			oops("dup2");
		close(fd);
		execvp(cmd,args);
		oops("execute");
	}
}

