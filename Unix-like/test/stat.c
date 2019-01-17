#include <stdio.h>
#include <sys/stat.h>

int main()
{
	struct stat infobuf;
	if(stat("/etc",&infobuf) == -1)
		perror("/etc");
	else
		printf("%o\n",infobuf.st_mode & S_IFMT);
	return 0;
}

