#include <iostream>
#include <math.h>

void cantor(int n)
{
	int i,j;
	int a,b;
	//calculate the layer
	double dec = (-1 + sqrt(1 + 8 * n))/2.0;
	if(static_cast<int>(dec * 10) % 10 > 0)
		i = static_cast<int>(dec) + 1;
	else
		i = static_cast<int>(dec);
	j = i * (i - 1) / 2;
	if(i % 2 != 0)
		a = i - n + j + 1,b = n - j; 
	else
		a = n - j,b = i - n + j + 1;
	std::cout<<a<<"/"<<b<<std::endl;
}

int main()
{
	int n;
	std::cin>>n;
	cantor(n);
	return 0;
}
