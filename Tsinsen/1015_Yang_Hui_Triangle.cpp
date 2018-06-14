#include <iostream>

int main()
{
	int i,j,n,tmp;
	std::cin>>n;
	int *result = new int[n * (n + 1) / 2];
	result[0] = 1;
	i = 0;
	while(i < n)
	{
		for(j = i * (i - 1) / 2;j <= i * (i + 1) / 2;j++)
			std::cout<<result[j]<<" ";
		std::cout<<std::endl;
		i++;
		for(j = i * (i - 1) / 2;j < i * (i + 1) / 2;j++)
			result[j] = 
	}
	delete [] result;
