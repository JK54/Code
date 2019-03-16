#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define IPV4(a,b,c,d) ((a<<0)|(b<<8)|(c<<16)|(d<<24))

int main()
{
	unsigned int value=IPV4(192,168,1,2);//这里是已逗号分开。
	printf("%u\n",value);
	in_addr_t ip;
	memcpy(&ip,&value,sizeof(value));
	printf("the ip value is %s\n",inet_ntoa(*((struct in_addr*)&ip)));
}
