#include <iostream>

int GCD(int m,int n)
{
	m = abs(m);
	n = abs(n);
	if(n>m)
	{
		int tmp = n;
		n = m;
		m = tmp;
	}
	if(n == 0)
		return m;
	else
		return GCD(n,m%n);
}

int main()
{
	std::cout<<GCD(6,5)<<std::endl;
}
