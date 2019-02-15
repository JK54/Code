#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void child_handler();
void child_execute();
void parent_execute();

int count = 0;
/* FILE *fp; */

int main()
{
	char tmp[10];
	int num_input,num_real,newpid;
	struct sigaction ssr;
	sigset_t blocked;
	printf("input child nums\n");
	fgets(tmp,strlen(tmp),stdin);
	num_input = atoi(tmp);
	ssr.sa_sigaction = child_handler;
	/* ssr.sa_flags = SA_SIGINFO; */
	ssr.sa_flags = SA_NODEFER;
	sigemptyset(&blocked);
	sigaddset(&blocked,SIGCHLD);
	ssr.sa_mask = blocked;
	sigaction(SIGCHLD,&ssr,NULL);
	/* fp = fopen("vvv","w"); */
	num_real = 0;
	for(int i = 0;i < num_input;i++)
	{
		if((newpid = fork()) == -1)
			perror("fork");
		else if(newpid == 0)
			child_execute();
		else
			num_real++;
	}
	sleep(1);
	printf("%d\n",num_real);
	while(count != num_real)
		parent_execute();
	/* fclose(fp); */
	printf("all done.\n");
}

void child_execute()
{
	printf("child : I am the child %d,waiting for 5 secs\n",getpid());
	sleep(5);
	exit(17);
}

void child_handler()
{
	int pid = wait(NULL);
	/* char tmp[54] = {"0"}; */
	/* snprintf(tmp,sizeof(tmp)/sizeof(tmp[0]),"handler : the child %d is dead,SIGCHLD captured.\n",pid); */
	/* fwrite(tmp,sizeof(char),strlen(tmp),fp); */
	count += 1;
}

void parent_execute()
{
	sleep(1);
	printf("parent : already handled %d.\n",count);
}
