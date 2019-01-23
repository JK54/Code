#include <iostream>
#include<algorithm>

void calcF(int n,int m,int &fn,int &fn1)
{
	int n1,n2,i;
	i = 1;
	if(n == 1)
	{
		fn = 1;
		fn1 = 1;
	}
	else if(n % 2 == 0)
	{
		calcF(n/2,m,n1,n2);
		fn = (n2 *n1 + n1 * ( n2 - n1 + m)) % m;
		fn1 = (n2 * n2 + n1 * n1) % m;
	}
	else
	{
		calcF(n/2,m,n1,n2);
		fn = (n1 * n1 + n2 * n2) % m;
		calcF(n/2 + 1,m,n1,n2);
		fn1 = (n2 * n1 + n1 * (n2 - n1 + m)) % m;
	}
}

int main()
{
	int n,m,fn,fn1;
	std::cin>>n>>m;
	calcF(n,m,fn,fn1);
	std::cout<<fn<<"\n"<<fn1<<std::endl;
	return 0;
}
