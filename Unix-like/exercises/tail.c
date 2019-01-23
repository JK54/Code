#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define COLUMN 11
#define LEN 512
int main(int argc,char **argv)
{
	FILE *stream;
	char line[COLUMN][LEN];
	int col = -1,set;
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
	while(fgets(line[(++col) % COLUMN],LEN,stream) != NULL);
	if(col < COLUMN)
		set = 0;
	else
		set = (col + 1) % COLUMN;
	while(set % COLUMN != col % COLUMN)
		fputs(line[set++ % COLUMN],stdout);
	fclose(stream);
	return 0;
}
