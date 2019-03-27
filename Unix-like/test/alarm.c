#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	alarm(1);
	while(1);
}
