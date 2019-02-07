#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void wakeup(int);

int main()
{
	signal(SIGALRM,wakeup);
	signal(SIGINT,wakeup);
	printf("dididi\n");
	alarm(4);
	pause();
	return 0;
}

void wakeup(int sec)
{
	printf("oops\n");
}
