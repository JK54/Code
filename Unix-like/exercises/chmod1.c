#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv)
{
	if(argc < 3)
	{
		perror("Usage:chmod mode filename");
		exit(1);
	}
	chmod(argv[2],atoi(argv[1]));
	return 0;
}

