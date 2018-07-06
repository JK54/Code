#include <iostream>
#include <string.h>

#define SIZE 3000

int factorial(int *result,int n)
{
	int tmp,i,j,r,len;
	len = 0;
	r = 0;
	result[0] = 1;
	len = 1;
	for(i = 2;i <= n;i++)
	{
		for(j = 0;j < len;j++)
		{
			tmp = result[j] * i + r;
			result[j] = tmp % 10;
			r = tmp / 10;
		}
		while(r != 0)
		{
			result[len++] = r % 10;
			r /= 10;
		}
	}
	return len;
}

int main()
{
	int n,len;
	int result[SIZE];
	memset(result,0,SIZE);
	std::cin>>n;
	len = factorial(result,n);
	for(int i = len - 1;i >= 0;i--)
		std::cout<<result[i];
	std::cout<<std::endl;
	return 0;
}
