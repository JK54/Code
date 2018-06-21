#include "include/sys_comm.h"

using namespace std;

size_t fibonacii_recursion(size_t n)
{
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;
	else
		return fibonacii_recursion(n - 1) + fibonacii_recursion(n - 2);
}
long double fibonacii_forward_iteration(size_t n)
{
	if(n <= 1)
		return n;
	else
	{
		long double f1 = 0,f2 = 1,current;
		for(size_t i = 0; i <= n; ++i)
		{
			current = f1 + f2;
			f1 = f2;
			f2 = current;
		}
		return current;
	}
	return -1;
}
long double fibonacii_calculte(size_t n)
{
	return 1/sqrt(5)*(pow((1 + sqrt(5)/2),n) - pow((1 - sqrt(5)/2),n));
}

long double fibonacii_iterate(size_t n)
{
	long double f = 0;
	long double g = 1;
	size_t i = 1;
	if(n > 1)
	{
		while( i < n--)
		{
			g = g + f;
			f = g - f;
		}
		return g;
	}
	else
		return -1;
}
int main()
{
	size_t a;
	cin>>a;
	cout<<fibonacii_iterate(a)<<endl;
	system("pause");
}
