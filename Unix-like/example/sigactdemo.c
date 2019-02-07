#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#define INPUTLEN 100

void inthandler(int s);
struct sigaction newhandler;
void inthandler(int s)
{
	printf("called with signal %d\n",s);
	sleep(s);
	printf("done handling signal %d\n",s);
}

int main()
{
	sigset_t blocked;
	char x[INPUTLEN];
	newhandler.sa_handler = inthandler;
	/* newhandler.sa_flags = SA_RESETHAND; */
	sigemptyset(&blocked);
	sigaddset(&blocked,SIGQUIT);
	newhandler.sa_mask = blocked;

	if(sigaction(SIGINT,&newhandler,NULL) == -1)
		perror("sigaction");
	else
		while(1)
		{
			fgets(x,INPUTLEN,stdin);
			printf("input : %s",x);
		}
	return 0;
}
