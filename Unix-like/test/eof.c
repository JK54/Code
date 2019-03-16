#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char buf[10][BUFSIZ];
	for(int i = 0;i < 10;i++)
		if(read(0,buf[i],BUFSIZ) == 0)
			break;
	for(int i = 0;i < 10 && buf[i] != NULL;i++)
		write(1,buf[i],strlen(buf[i]));
}
