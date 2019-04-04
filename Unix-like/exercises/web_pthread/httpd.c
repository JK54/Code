#include "webserver.h"
#include <fcntl.h>
#define PORT "13194" 
#define BACKLOG 5

static int sock_id;
static int sock_fd = -1;
static char **argbuf = NULL;
static bool re_ship = false;

void free_fd()
{
	if(sock_fd != -1)
	{
		close(sock_fd);
		sock_fd = -1;
	}
	if(argbuf != NULL)
	{
		freelist(argbuf);
		argbuf = NULL;
	}
}

void process_request()
{
	char buf[BUFSIZ];
	char res[BUFSIZ];
	int record = open("history.dat",O_CREAT | O_WRONLY ,0644);
	while(1)
	{
		sock_fd = server_accept_socket(sock_id,record);
		if(re_ship == false)
		{
			memset(buf,'\0',BUFSIZ);
			if(read(sock_fd,buf,BUFSIZ) > 0)
				argbuf = split_args(buf);
			if(argbuf != NULL && (strncmp(argbuf[0],"GET",3) == 0) && (strlen(argbuf[0]) == 3))
			{
				if(!is_exist(argbuf[1]))
				{
					error_404(sock_fd,argbuf[1]);
					snprintf(res,BUFSIZ,"%s","not exist\n\n");
				}
				else if(is_dir(argbuf[1]))
				{
					do_ls(sock_fd,argbuf[1]);
					snprintf(res,BUFSIZ,"%s","request directory\n\n");
				}	
				else if(is_cgi(argbuf[1]))
				{
					do_exec(sock_fd,argbuf[1]);
					snprintf(res,BUFSIZ,"%s","request cgi\n\n");
				}
				else
				{
					do_cat(sock_fd,argbuf[1]);
					snprintf(res,BUFSIZ,"%s","request html\n\n");
				}
			}
			else if(argbuf != NULL && (strncmp(argbuf[0],"HEAD",4) == 0) && (strlen(argbuf[0]) == 4))
			{
				header(sock_fd,"header");
				snprintf(res,BUFSIZ,"%s","request head\n\n");
			}
			else if(argbuf != NULL && (strncmp(argbuf[0],"POST",4) == 0) && (strlen(argbuf[0]) == 4))
			{
				snprintf(res,BUFSIZ,"%s\n",argbuf[1]);
			}
			else
			{
				error_501(sock_fd);
				snprintf(res,BUFSIZ,"%s","not a command\n\n");
			}
			write(record,res,strlen(res));
		}
		else
			re_ship =  false;
		free_fd();
	}
	close(record);
}

void handler_int()
{
	signal(SIGINT,handler_int);
	if(sock_fd != -1)
	{
		char mesg[] = "shut down by server\n";
		write(sock_fd,mesg,strlen(mesg));
	}
	free_fd();
	re_ship = true;
}

void child_waiter()
{
	signal(SIGCHLD,child_waiter);
	while(waitpid(-1,NULL,WNOHANG) > 0);
}

void set_signal_handler()
{
/*
 *     struct sigaction child,inter;
 * 
 *     child.sa_sigaction = child_waiter;
 *     child.sa_flags = SA_SIGINFO;
 *     sigemptyset(&child.sa_mask);
 *     sigaction(SIGCHLD,&child,NULL);
 * 
 *     inter.sa_sigaction = handler_int;
 *     inter.sa_flags = SA_SIGINFO;
 *     sigemptyset(&inter.sa_mask);
 *     sigaction(SIGINT,&inter,NULL);
 */
	signal(SIGCHLD,child_waiter);
	signal(SIGINT,handler_int);
}

int main()
{
	sock_id = make_server_socket(PORT,BACKLOG);
	set_signal_handler();
	process_request();
	close(sock_id);
}
