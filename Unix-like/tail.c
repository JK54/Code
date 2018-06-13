#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define COLUMN 24
int main(int argc,char **argv)
{
	FILE *stream;
	char *line[COLUMN];
	int Pos[COLUMN],pos = 0,index = 0;
	if(argc != 2)
	{
		perror("Usage: tail file");
		exit(1);
	}
	stream = fopen(argv[1],"r");
	if(stream == NULL)
	{
		perror("Error opening file");
		exit(1);
	}
	fseek(stream,0,SEEK_END);
	while(index < COLUMN && (pos = fseek(stream,1,SEEK_CUR) == 0))
	{
		if()
	}
}
