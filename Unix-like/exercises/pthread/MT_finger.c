#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct record
{
	int no;
	char time[11];
	char str[BUFSIZ];
	struct record *next;
};

struct table
{
	int num;
	struct record *head;
};
static struct table database;
static int rps;

void setup()
{
	char buf[BUFSIZ];
	struct record *tmp;

	rps = 0;
	FILE *fp = fopen("./database","r");
	if(fread(buf,sizeof(char),BUFSIZ,fp) > 0)
	{
		tmp = malloc(sizeof(struct record));
	}
	while(fread(buf,sizeof(char),BUFSIZ,fp) > 0)
	{
		
	}
}

int main()
{
	setup();
}
