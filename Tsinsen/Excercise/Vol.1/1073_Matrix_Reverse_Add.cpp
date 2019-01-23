#include <iostream>

void add(int **data,int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
			std::cout<<(data[i][j] + data[j][i])<<" ";
		std::cout<<std::endl;
	}
}

int main()
{
	int n,i,j,**data;
	std::cin>>n;
	data = new int *[n];
	for(i = 0;i < n;i++)
		data[i] = new int [n];
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			std::cin>>data[i][j];
	add(data,n);
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	return 0;
}
