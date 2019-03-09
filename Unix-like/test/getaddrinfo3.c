#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/socket.h>
int main()
{ 
	struct addrinfo *ailist, *aip; 
	struct addrinfo hint; 
	struct sockaddr_in *sinp; 
	char *hostname = "localhost";
	char buf[INET_ADDRSTRLEN]; 
	char *server = "6543"; /* 这是服务端口号 */
	const char *addr; 
	int ilRc;
	hint.ai_family = AF_UNSPEC; /* hint 的限定设置 */
	hint.ai_socktype = 0; /* 这里可是设置 socket type . 比如 SOCK——DGRAM */
	hint.ai_flags = AI_PASSIVE; /* flags 的标志很多 。常用的有AI_CANONNAME; */
	hint.ai_protocol = 0; /* 设置协议 一般为0，默认 */ 
	hint.ai_addrlen = 0; /* 下面不可以设置，为0，或者为NULL */
	hint.ai_canonname = NULL; 
	hint.ai_addr = NULL; 
	hint.ai_next = NULL;
	ilRc = getaddrinfo(hostname, server, &hint, &ailist); 
	if (ilRc < 0) 
	{ 
		printf("str_error = %s\n", gai_strerror(errno)); 
		return 1; 
	}
 
	/* 显示获取的信息 */
	for (aip = ailist; aip != NULL; aip = aip->ai_next)
	{ 
		sinp = (struct sockaddr_in *)aip->ai_addr;
		addr = inet_ntop(AF_INET, &sinp->sin_addr, buf, INET_ADDRSTRLEN); 
		printf(" addr = %s, port = %d\n", addr?addr:"unknow ", ntohs(sinp->sin_port)); 
	}
	return 0;
}
/*
 * 
 * --------------------- 
 * 作者：prettyshuang 
 * 来源：CSDN 
 * 原文：https://blog.csdn.net/prettyshuang/article/details/50457086 
 * 版权声明：本文为博主原创文章，转载请附上博文链接！
 */
