#include <iostream>

int main()
{
	int i,j,n;
	int *data,tmp;
	std::cin>>n;
	data = new int [n];
	for(i = 0;i < n;i++)
		std::cin>>data[i];
	for(i = 0;i < n;i++)
	{
		tmp = data[i];
		for(j = i + 1;j < n;j++)
		{
			if(tmp > data[j])
			{
				tmp = data[j];
				data[j] = data[i];
				data[i] = tmp;
			}
		}
	}
	for(i = 0;i < n;i++)
		std::cout<<data[i]<<" ";
	std::cout<<std::endl;
	delete [] data;
	return 0;
}
