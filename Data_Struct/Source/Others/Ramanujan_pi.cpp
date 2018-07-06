#include "include/sys_comm.h"

#define N 3


long double factorial(int n)
{
	if(n == 0)
		return 1;
	else
		return 1*factorial(n - 1);
}
	
int main()
{
	long double a[N];
	for(int i = 0;i < N; ++i)
		{
			a[i] = (factorial(4 * i) *(1103 + 26390*i))/(pow(factorial(i),4)*pow(396,4*i));
		}
	long double aa = 0;
	for(auto i:a)
		aa += i;
	long double pi = 9801/(sqrt(8)*aa);
	std::cout<<std::setprecision(100)<<pi<<std::endl;
}
