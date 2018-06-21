#include <iostream>
#include <math.h>

int factor(int n)
{
	int tmp = 2;
	if(n == 1)
		return 1;
	for(int i = 2;i <= sqrt(n);i++)
	{
		if(n % i == 0)
		{
			if(n / i == i)
				tmp++;
			else
				tmp += 2;
		}
	}
	return tmp;
}
int main()
{
	int n,result;
	std::cin>>n;
	result = factor(n);
	std::cout<<result<<std::endl;
}
