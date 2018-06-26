#include <iostream>
#define SIZE 100

int fibonacci(int n)
{
	int i,tmpa,tmpb,tmpc,result;
	result = 0;
	if(n == 2)
		result = 2;
	else if(n == 1)
		result = 1;
	else
	{
		tmpa = 1;
		tmpb = 1;
		tmpc = 2;
		for(i = 2;i <= n;i++)
		{
			result += tmpc;
			tmpc = tmpa + tmpb;
			tmpa = tmpb;
			tmpb = tmpc;
		}
	}
	return result;
}
int main()
{
	int i,j,tmp;
	int rf[SIZE];
	for(i = 0;i < SIZE;i++)
	{
		std::cin>>tmp;
		if(tmp == 0)
			break;
		else
			rf[i] = tmp;
	}
	for(j = 0;j < i;j++)
	{
		rf[j] = fibonacci(rf[j]);
		std::cout<<rf[j]<<std::endl;
	}
	return 0;
}
