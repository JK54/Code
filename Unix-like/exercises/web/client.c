#include "webserver.h"

#define SERVER "127.0.0.1"
#define PORT "13194"

int main(int argc,char **argv)
{
	int sock_id;
	sock_id = connect_to_server(SERVER,PORT);
	char cmd[] = "GET hello.cgi HTTP/1.0";
	size_t size = strlen(cmd);
	write(sock_id,cmd,size);
	char buf[BUFSIZ];
	while(read(sock_id,buf,BUFSIZ) > 0)
	{
		write(STDOUT_FILENO,buf,strlen(buf));
		memset(buf,'\0',BUFSIZ)	;
	}
	return 0;
}
