#include <stdio.h>
#include <string.h>

int main()
{
	char buf[BUFSIZ] = "abcdefghijklmn";
	char tmp[BUFSIZ] = "opqrstuvwxyz";
	printf("%s\n",buf);
	snprintf(buf,2,"%s",tmp);
	printf("%s\n",buf);
}
