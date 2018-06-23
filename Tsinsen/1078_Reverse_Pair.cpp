#include <iostream>

int findpair(int n,int *data)
{
	int i,j,count;
	count = 0;
	for(i = 0;i < n;i++)
	{
		for(j = i + 1;j < n;j++)
		{
			if(data[i] > data[j])
				count++;
		}
	}
	return count;
}
int main()
{
	int n,*data;
	std::cin>>n;
	data = new int [n];
	for(int i = 0;i < n;i++)
		std::cin>>data[i];
	std::cout<<findpair(n,data)<<std::endl;
	delete [] data;
	return 0;
}
