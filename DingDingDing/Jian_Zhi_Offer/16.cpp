#include <iostream>

double fastpow(double base,int exponent)
{
	if(base == 0)
	{
		if(exponent < 0)
			throw "div by zero";
		else
			return 0;
	}
	int absexponent = abs(exponent);
	bool negative = exponent < 0 ? true : false;
	double result = 1;
	while(absexponent != 0)
	{
		if(absexponent & 1)
			result *= base;
		absexponent >>= 1;
		base *= base;
	}
	if(negative)
		result = 1 / result;
	return result;
}

int main()
{
	double base;
	int exponent;
	std::cin>>base>>exponent;
	try
	{
		double result = fastpow(base,exponent);
		std::cout<<result<<std::endl;
	}
	catch(char const* msg)
	{
		std::cerr<<msg<<std::endl;
	}
}
