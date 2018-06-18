#include <iostream>
#define SIZE 100

int fibonacci(int n)
{
	int i,tmpa,tmpb,result;
	if(n == 2)
		result = 1;
	else if(n == 1)
		result = 0;
	else
	{
		tmpa = 0;
		tmpb = 1;
		for(i = 2;i < n;i++)
		{
			result = tmpa + tmpb;
			tmpa = tmpb;
			tmpb = result;
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
