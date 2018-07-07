#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

double f(double x)
{
	return pow(x,3) - 5 * pow(x,2) + 6 * x - 10;
}
double getRoot(double (*f)(double), double a, double b)
{ 
	double p;
	p = (a + b) / 2;
	while(!(f(p) < 1e-6 && f(p) > -1e-6))
	{
		p = (a + b) / 2;
		if(f(p) * f(b) < 0)
			a = p;
		else if(f(p) * f(b) > 0)
			b = p;
	}
	return p;
}

int main()
{
	double a,b;
	cin>>a>>b;
	cout<<getRoot(f,a,b)<<endl;
	return 0;
}

