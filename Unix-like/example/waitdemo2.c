#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define DELAY 5

int main()
{
	int newpid;
	void chid_code(),parent_code();
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
	sleep(delay);
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
