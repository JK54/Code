#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define testfile "11.txt"

int main()
{
	int fd,pid;
	char msg1[] = "Test 1 2 3 ..\n";
	char msg2[] = "Hello,hello\n";
	if((fd = creat(testfile,0644)) == -1)
		return 0;
	if(write(fd,msg1,strlen(msg1)) == -1)
		return 0;
	if((pid = fork()) == -1)
		return 0;
	if(write(fd,msg2,strlen(msg2)) == -1)
		return 0;
	  close(fd);
	  return 1;
}
