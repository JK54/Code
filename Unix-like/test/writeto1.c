#include <stdio.h>
#include <unistd.h>

int main()
{
	char *a = "asad";
	write(1,a,sizeof(a));
	write(1,"\n",1);
}
