#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define DELAY 5

int main()
{
	int newpid;
	int process_num,*child_processes;
	void chid_code(),parent_code();
	printf("input the num of process\n");
	scanf("%d",&process_num);
	printf("before:my pid is %d\n",getpid());
	child_processes = malloc(sizeof(int) * process_num);
	for(int i = 0;i < process_num;i++)
	{
		srand(time(0));
		if((newpid = fork()) == -1)
			perror("fork");
		else if (newpid == 0)
			chid_code(rand() % DELAY);
		else
			child_processes[i] = newpid;
	}
	for(int i = 0;i < process_num;i++)
		parent_code(child_processes[i]);
	free(child_processes);
	return 0;
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
	int wait_rv;
	/* int child_status,high_8,low_7,bit_7; */
	/* wait_rv = wait(&child_status); */
	wait_rv = wait(NULL);
	printf("done waiting for %d.Waiting return: %d\n",child_pid,wait_rv);
	/* high_8 = child_status >> 8; */
	/* low_7 = child_status & 0x7F; */
	/* bit_7 = child_status & 0x80; */
	/* printf("status:exit = %d,sig = %d,core = %d\n",high_8,low_7,bit_7); */
}
