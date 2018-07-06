#include <iostream>

void derivate(int k,int n,int *a,int *b)
{
	int i,j,f;
	f = -1;
	for(i = 0;i < n;i++)
	{
		b[i] -= k;
		if(b[i] >= 0)
			for(j = 1;j <= k;j++)
				a[i] *= (j + b[i]);
	}
	std::cout<<"f";
	for(i = 0;i < k;i++)
		std::cout<<"'";
	std::cout<<"(x)=";
	for(i = 0;i < n;i++)
		if(b[i] >= 0)
			{
				f = i;
				break;
			}
	for(i = 0;i < n;i++)
	{
		if(b[i] >= 0)
		{
			if(a[i] > 0 && i != f)
				std::cout<<"+";
			std::cout<<a[i];
			if(b[i] >= 1)
				std::cout<<"*"<<"x";
			if(b[i] > 1)
				std::cout<<"^"<<b[i];
		}
	}
	if(f == -1)
		std::cout<<"0";
	std::cout<<std::endl;
}
int main()
{
	int k,n,*a,*b;
	std::cin>>k>>n;
	a = new int [n];
	b = new int [n];
	for(int i = 0;i < n;i++)
		std::cin>>a[i]>>b[i];
	derivate(k,n,a,b);
	delete [] a;
	delete [] b;
	return 0;
}
