#include<iostream>
#include <math.h>
#include <iomanip>
static int a,b,c,d;

double f(double x)
{
	return a * pow(x,3) + b * pow(x, 2) + c * x + d;
}
double ff(double x)
{
	return 3 * a * pow(x,2) + 2 * b * x + c;
}

int main()
{
	double z,result;
	int count = 1;
	std::cin>>a>>b>>c>>d>>z;
	result = z;
	while(fabs(f(result)) > 1e-7)
	{
		count++;
		result = result - f(result)/ff(result);
	}
	std::cout<<std::fixed<<std::setprecision(3)<<result<<" "<<count<<std::endl;
	return 0;
}
