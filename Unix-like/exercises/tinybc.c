#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


void dc(int todc[],int fromdc[]);
void bc(int todc[],int fromdc[]);
int oops(char *m,int x) {perror(m);exit(x);}

int main()
{
	int todc[2],fromdc[2];
	int pid;
	if(pipe(todc) == -1 || pipe(fromdc) == 1)
		oops("pipe failed",1);
	if((pid = fork()) == -1)
		oops("fork failed",2);
	if(pid == 0)
		dc(todc,fromdc);
	else
	{
		bc(todc,fromdc);
		wait(NULL);
	}
}

void dc(int todc[],int fromdc[])
{
	if(dup2(todc[0],0) == -1)
		oops("dc:redirect stdin failed",3);
	close(todc[0]);
	close(todc[1]);
	if(dup2(fromdc[1],1) == -1)
		oops("dc:redirect stdout failed",4);
	close(fromdc[0]);
	close(fromdc[1]);
	/* execlp("dc","dc","-"); */
	execlp("dc","dc","-",NULL);
	oops("dc: run failed",5);
}

void bc(int todc[],int fromdc[])
{
	int num1,num2;
	char op,message[BUFSIZ];
	FILE *fpout,*fpin,*fdopen();
	close(todc[0]);
	close(fromdc[1]);
	fpout = fdopen(todc[1],"w");
	fpin = fdopen(fromdc[0],"r");
	if(fpout == NULL || fpin == NULL)
		oops("bc : convert pipes to streams failed",1);
	while(1)
	{
		printf("tinybc : ");
		if(fgets(message,BUFSIZ,stdin) == NULL)
		{
			printf("bc : read from stdin failed\n");
			break;
		}
		if(sscanf(message,"%d%c%d",&num1,&op,&num2) != 3)
		{
			printf("bc : syntax error\n");
			continue;
		}
		if(fprintf(fpout,"%d\n%d\n%c\np\n",num1,num2,op) == EOF)
		{
			printf("bc : write to dc failed\n");
			break;
		}
		fflush(fpout);
		if(fgets(message,BUFSIZ,fpin) == NULL)
		{
			printf("bc : read from dc failed\n");
			break;
		}		
		printf("%d %c %d = %s\n",num1,op,num2,message);
	}
	fclose(fpin);
	fclose(fpout);
}
