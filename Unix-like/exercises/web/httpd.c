#include "webserver.h"

#define PORT "13194" 
#define BACKLOG 2

int main()
{
	int sock_id,sock_fd;
	char buf[BUFSIZ];
	char **argbuf;

	sock_id = make_server_socket(PORT,BACKLOG);
	signal(SIGCHLD,child_waiter);
	while(1)
	{
		sock_fd = server_accept_socket(sock_id);
		memset(buf,'\0',BUFSIZ);
		read(sock_fd,buf,BUFSIZ);
		argbuf = split_args(buf);
		if((strncmp(argbuf[0],"GET",3) == 0) && (strlen(argbuf[0]) == 3))
		{
			if(!is_exist(argbuf[1]))
				error_404(sock_fd,argbuf[1]);
			else if(is_dir(argbuf[1]))
				do_ls(sock_fd,argbuf[1]);
			else if(is_cgi(argbuf[1]))
				do_exec(sock_fd,argbuf[1]);
			else
				do_cat(sock_fd,argbuf[1]);
		}
		else
			error_501(sock_fd);
		close(sock_fd);
		freelist(argbuf);
	}
	close(sock_id);
}
