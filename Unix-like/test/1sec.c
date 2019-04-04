#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int i = 0;

void ff(int signum)
{
	printf("%d\n",i);
	exit(signum);
}

int main()
{
	signal(SIGALRM,ff);
	alarm(1);
	while(1)
		i++;
}
