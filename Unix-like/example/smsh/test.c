#include <stdlib.h>
#include <stdio.h>
#include 

bool dididi(int arg)

int main()
{
	int a,b,c;
	b = 1;
	c = 0;
	while( ++b != 5 && dididi(b));
}

bool dididi(int arg)
{
	printf("%d\n",arg);
	return true;
}
