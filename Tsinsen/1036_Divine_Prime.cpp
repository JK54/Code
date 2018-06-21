#include <iostream>

bool isprime(int n,int &part)
{
	for(int i = 2;i < n;i++)
		if(n % i == 0)
		{
			part = i;
			return false;
		}
	if(n == 1 || n == 0)
	{
		part = -1;
		return false;
	}
	part = n;
	return true;
}

void depart(int a,int b)
{
	int i,j,k;
	for(i = a;i <= b;i++)
	{
		if(!isprime(i,j))
		{
			if(j != -1)
			{
				std::cout<<i<<"="<<j;
				k = i/j;
				while(!isprime(k,j))
				{
					std::cout<<"*"<<j;
					k = k/j;
				}
				std::cout<<"*"<<k<<std::endl;
			}
			//1
			else
				std::cout<<i<<"="<<i<<std::endl;
		}
		else
			std::cout<<i<<"="<<i<<std::endl;
	}
}

int main()
{
	int a, b;
	std::cin>>a>>b;
	depart(a,b);
	return 0;
}
