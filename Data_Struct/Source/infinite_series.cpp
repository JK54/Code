#include "../Include/sys_comm.h"

double f(double x)
{
	double S = 1,t = 1;
	int n = 1;
	while(fabs(t) >= 1e-6)
	{
		t = t*x/n;
		n++;
		S += t;
	}
	return S;
}

int main()
{
	std::cout<<f(1)<<std::endl;
}
