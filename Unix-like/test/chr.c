#include <stdio.h>
#include <string.h>

int main()
{
	char ss[4] = {"text"};
	printf("%lu,%lu,%s\n",sizeof(ss),strlen(ss),ss);
}
