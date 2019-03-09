/*
 * --------------------- 
 * 作者：pdcxs007 
 * 来源：CSDN 
 * 原文：https://blog.csdn.net/pdcxs007/article/details/44812451 
 * 版权声明：本文为博主原创文章，转载请附上博文链接！
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>

void printAddressInfo(const struct addrinfo*);

int main(int argc, char* argv[])
{
    int n;
    struct addrinfo hint,*res, *ressave;
    char* serv;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: "
                "./getaddrinfo <hostname> [<service name"
                " or port name>]\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
        serv = NULL;    
	else
        serv = argv[2];
    bzero(&hint, sizeof(hint));
    hint.ai_family = AF_UNSPEC;

    if ((n = getaddrinfo(argv[1], serv, &hint, &res)) != 0)
    {
        if (argc > 2)
            fprintf(stderr, "Cannot get information for "
                    "%s : %s\n\terror:%s\n",
                    argv[1], serv, gai_strerror(n));
        else
            fprintf(stderr, "Cannot get information for "
                    "%s\n\terror:%s\n",
                    argv[1], gai_strerror(n));
        exit(EXIT_FAILURE);
    }
    ressave = res;

    while (res != NULL)
    {
        printAddressInfo(res);
        res = res->ai_next;
    }

    freeaddrinfo(ressave);
    exit(EXIT_SUCCESS);
}

void printAddressInfo(const struct addrinfo* addr)
{
    char str[INET6_ADDRSTRLEN];
    short port;

    printf("ai_family: ");
    switch (addr->ai_family)
    {
        case AF_INET: {
            struct sockaddr_in* in;

            printf("ipv4\n");
            in = (struct sockaddr_in *)(addr->ai_addr);
            port = ntohs(in->sin_port);
            inet_ntop(AF_INET, &in->sin_addr, str, sizeof(str));
            break;
        }
        case AF_INET6: {
            struct sockaddr_in6* in6;

            in6 = (struct sockaddr_in6 *)(addr->ai_addr);
            port = ntohs(in6->sin6_port);
            inet_ntop(AF_INET6, &in6->sin6_addr, str, sizeof(str));
            printf("ipv6\n");
            break;
        }
        default:
            printf("Unknown\n");
            break;
    }
    printf("ai_socktype: ");
    switch (addr->ai_socktype)
    {
        case SOCK_STREAM:
            printf("stream\n");
            break;
        case SOCK_DGRAM:
            printf("dgram\n");
            break;
        case SOCK_SEQPACKET:
            printf("seqpacket\n");
            break;
        case SOCK_RAW:
            printf("raw\n");
            break;
        default:
            printf("others\n");
            break;
    }
    printf("protocol: ");
    switch (addr->ai_protocol)
    {
        case IPPROTO_TCP:
            printf("tcp\n");
            break;
        case IPPROTO_UDP:
            printf("udp\n");
            break;
        case IPPROTO_SCTP:
            printf("sctp\n");
            break;
        default:
            printf("others\n");
            break;
    }
    printf("address: %s\n", str);
    printf("port: %d\n", port);
    printf("canonical name: %s\n\n", addr->ai_canonname);
}

