#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char buf[BUFSIZ];
	while(read(0,buf,BUFSIZ) != 0)
		write(1,buf,strlen(buf));
}
