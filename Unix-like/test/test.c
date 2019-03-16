#include <stdio.h>

int main()
{
	char buf[BUFSIZ];
	while(fgets(buf,BUFSIZ,stdin) != NULL)
		printf("%s",buf);
}
