#include <iostream>
void purchase(int **data,int n,int m)
{
	int i,j,tmp;
	for(j = 0;j < m;j++)
	{
		tmp = 1;
		for(i = 0;i < n;i++)
		{
			if((data[tmp - 1][j] >= data[i][j] && data[i][j] != 0) || (data[tmp - 1][j] < data[i][j] && data[tmp - 1][j] == 0))
				tmp = i + 1;
		}
		if(data[tmp - 1][j] == 0)
			tmp = 0;
		std::cout<<tmp<<" ";
	}
	std::cout<<std::endl;
}
int main()
{
	int n,m,**data;
	int i,j;
	std::cin>>n>>m;
	data = new int * [n];
	for(i = 0;i < n;i++)
		data[i] = new int[m];
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < m;j++)
			std::cin>>data[i][j];
	}
	purchase(data,n,m);
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	return 0;
}
