#include <iostream>
#include <math.h>

int main()
{
	int i;
	for(i = 1000;i <=9999;i++)
		if((i / 1000 == i %10) && (i / 100 % 10 == i /10 % 10))
			std::cout<<i<<std::endl;
	return 0;
}
