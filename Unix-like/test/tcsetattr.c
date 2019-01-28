#include <stdio.h>
#include <termio.h>

int main()
{
	static struct termios ori;
	tcgetattr(0,&ori);
}
