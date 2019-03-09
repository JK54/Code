#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
 
int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usag: ./a.out hostname|ip\n");
        exit(1);
    }
    struct addrinfo hints;
    struct addrinfo *res, *cur;
    int ret;
    struct sockaddr_in *addr;
    char ipbuf[16];
	int port;
 
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* Allow IPv4 */
    hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_socktype = SOCK_DGRAM;
	ret = getaddrinfo(argv[1],NULL,&hints,&res);
    if (ret < 0) {
		fprintf(stderr, "%s\n", gai_strerror(ret));
        exit(1);
    }
    
    for (cur = res; cur != NULL; cur = cur->ai_next) {
        addr = (struct sockaddr_in *)cur->ai_addr;
		short a = 5;
		memset(&addr->sin_port,a,sizeof(in_port_t));
        printf("ip: %s\n", inet_ntop(AF_INET, &addr->sin_addr, ipbuf, 16));
		/* printf("port: %d\n", inet_ntop(AF_INET, &addr->sin_port, (void *)&port, 2)); */
		/* printf("port: %d\n", addr->sin_port); */
		/* printf("port: %d\n", ntohs(addr->sin_port)); */
		
    }
    freeaddrinfo(res);
    exit(0);
}
/*
 * --------------------- 
 * 作者：prettyshuang 
 * 来源：CSDN 
 * 原文：https://blog.csdn.net/prettyshuang/article/details/50457086 
 * 版权声明：本文为博主原创文章，转载请附上博文链接！
 */
