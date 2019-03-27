#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	printf("SuperSleep version 1.0 Running\tLicensed Software\n");
	while(1)
	{
		printf("%d..\n",i);
		sleep(5);
		i += 5;
	}
	printf("The super sleep program ran as expect.\n");
	return 0;
}
