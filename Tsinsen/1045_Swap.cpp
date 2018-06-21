#include <iostream>

int main()
{
	int t,**data,*m,*n;
	int i,j,tmpx,tmpy;
	std::cin>>t;
	data = new int* [t];
	m = new int[t];
	n = new int[t];
	for(i = 0;i < t;i++)
	{
		std::cin>>n[i]>>m[i];
		data[i] = new int[n[i]];
		for(j = 0;j < n[i];j++)
			std::cin>>data[i][j];
		for(j = 0;j < m[i];j++)
		{
			std::cin>>tmpx>>tmpy;
			std::swap(data[i][tmpx],data[i][tmpy]);
		}
	}
	for(i = 0;i < t;i++)
	{
		for(j = 0;j < n[i];j++)
			std::cout<<data[i][j]<<std::endl;
	}
	for(i = 0;i < t;i++)
		delete [] data[i];
	delete [] data;
	delete [] m;
	delete [] n;
	return 0;
}
