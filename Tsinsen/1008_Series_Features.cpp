#include <iostream>

int main()
{
	int n,*ele;
	int max,min,sum;
	std::cin>>n;
	ele = new int[n];
	for(int i = 0;i < n;i++)
		std::cin>>ele[i];
	max = min = ele[0];
	sum = 0;
	for(int i = 0;i < n;i++)
	{
		if(max < ele[i])
			max = ele[i];
		if(min > ele[i])
			min = ele[i];
		sum += ele[i];
	}
	std::cout<<max<<"\n"<<min<<"\n"<<sum<<std::endl;
}
