#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define COLUMN 24
#define LEN 512
int main(int argc,char **argv)
{
	FILE *stream;
	char line[LEN];
	int col = COLUMN;
	if(argc != 2)
	{
		perror("Usage: head file");
		exit(1);
	}
	stream = fopen(argv[1],"r");
	if(stream == NULL)
	{
		perror("Error opening file");
		exit(1);
	}
	while(col > 0 && fgets(line,512,stream) != NULL )
	{
		fputs(line,stdout);
		col--;
	}
	return 0;
}
