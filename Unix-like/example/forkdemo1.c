#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main()
{
	pid_t ret_from_fork,mypid;
	mypid = getpid();
	printf("before,my pid is %d\n",mypid);
	ret_from_fork = fork();
	sleep(1);
	printf("after,my pid is %d,fork() said %d\n",getpid(),ret_from_fork);
}
