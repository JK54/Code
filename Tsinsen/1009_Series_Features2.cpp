#include <iostream>
#include <math.h>

int main()
{
	int n,*ele;
	int tmp,sqsum = 0;
	int i,j;
	std::cin>>n;
	ele = new int[n];
	for(i = 0;i < n;i++)
		std::cin>>ele[i];
	for(i = 1;i < n;i++)
	{
		if(ele[i - 1] > ele[i])
		{
			tmp = ele[i];
			for(j = i;j >= 1 && tmp < ele[j - 1];j--)
				ele[j] = ele[j - 1];
			ele[j] = tmp;
		}
	}
	for(i = 0;i < n;i++)
		sqsum += pow(ele[i],2);
	std::cout<<ele[n - 2]<<'\n'<<ele[1]<<'\n'<<sqsum<<std::endl;
}
