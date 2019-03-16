#include <unistd.h>
#include <stdio.h>

int main()
{
	execlp("ls","ls","--color=auto","/home/jk54",NULL);
}
