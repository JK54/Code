#include <iostream>

void draw(int n)
{
	int i,j,count,size,**data;
	count = 1;
	size = n * n;
	//left,right,up,down ,flag of direction
	data = new int *[n];
	for(i = 0;i < n;i++)
		data[i] = new int [n];
	i = 0;
	j = -1;	
	while(count <= n * n)
	{
		while(count <= n * n && j < n - i - 1)
			data[i][++j] = count++;
		while(count <= n * n && i < j)
			data[++i][j] = count++;
		while(count <= n * n && j > n - i - 1)
			data[i][--j] = count++;
		while(count <= n * n && i > j + 1)
			data[--i][j] = count++;
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
			std::cout<<data[i][j]<<" ";
		std::cout<<std::endl;
	}
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
}

int main()
{
	int n;
	std::cin>>n;
	draw(n);
	return 0;
}
