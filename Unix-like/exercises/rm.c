#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	if(argc == 1)
		perror("Usage: rm file1 file2 ..");
	else
		for(int i = 1;i < argc;i++)
			unlink(argv[i]);
	return 0;
}
