#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define DELAY 2

int main()
{
	int newpid;
	void chid_code(),parent_code(),child_handler();
	signal(SIGCHLD,child_handler);
	printf("before:my pid is %d\n",getpid());
	if((newpid = fork()) == -1)
		perror("fork");
	else if (newpid == 0)
		chid_code(DELAY);
	else
		parent_code(newpid);
}

void chid_code(int delay)
{
	printf("child %d here,will delay for %d seconds\n",getpid(),delay);
	for(int i = 0;i < delay;i++)
	{
		sleep(1);
		printf("waiting..\n");
	}
	printf("child done,about to exit\n");
	exit(17);
}

void parent_code(int child_pid)
{
	int wait_rv,child_status;
	int high_8,low_7,bit_7;
	wait_rv = wait(&child_status);
	printf("done waiting for %d.Waiting return: %d\n",child_pid,wait_rv);
	high_8 = child_status >> 8;
	low_7 = child_status & 0x7F;
	bit_7 = child_status & 0x80;
	printf("status:exit = %d,sig = %d,core = %d\n",high_8,low_7,bit_7);
}

void child_handler(int signum)
{
	printf("received signal %d\n",signum);
}
