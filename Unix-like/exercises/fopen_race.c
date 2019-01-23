#include <stdio.h>
#include <unistd.h>

int main()
{
	unlink("11.txt");
	FILE *f1,*f2;
	f1 = fopen("11.txt","a");
	f2 = fopen("11.txt","a");
	for(int i = 1;i < 1000;i++)
	{
		if(i % 2 == 1)
			fprintf(f1,"%d ",i);
		else
			fprintf(f2,"%d ",i);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
