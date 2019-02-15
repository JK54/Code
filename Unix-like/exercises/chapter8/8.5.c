#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define testfile "12.txt"

int main()
{
	FILE *fp;
	int pid;
	char msg1[] = "Test 1 2 3 ..\n";
	char msg2[] = "Hello,hello\n";
	if((fp = fopen(testfile,"w")) == NULL)
		return 0;
	fprintf(fp,"%s",msg1);
	if((pid = fork()) == -1)
		return 0;
	fprintf(fp,"%s",msg2);
	fclose(fp);
	return 1;
}
