#include <iostream>

int main()
{
	int i,j,n;
	std::cin>>n;
	int *result = new int[n * (n + 1) / 2];
	for(i = 1;i <= n;i++)
	{
		for(j = i * (i - 1) / 2;j < i * (i + 1) / 2;j++)
		{
			if(j == i * (i - 1) / 2 || j == i * (i + 1) / 2 - 1)
				result[j] = 1;
			else
				result[j] = result[j - i] + result[j - i + 1];
		}
		for(j = i * (i - 1) / 2;j < i * (i + 1) / 2;j++)
			std::cout<<result[j]<<" ";
		std::cout<<std::endl;
	}
	delete [] result;
}
