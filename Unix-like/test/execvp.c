#include <unistd.h>
#include <stdio.h>

int main()
{
	char a[][2] = {"-l","."};
	execvp(a[0],a);
}
