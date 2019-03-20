#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <wait.h>

int connect_to_server(char *hostname,char *servname);
int talk_with_server(FILE *fp);
int make_server_socket(char *servname,int backlog);
void process_request_fork(int fd,char *cmd,char **args);
void child_waiter(int signum);
int server_accept_socket(int sock_fd);

#define oops(m){perror(m);exit(EXIT_FAILURE);}
