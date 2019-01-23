#include <iostream>

void draw(int **data,int n)
{
	int i,j,k,count,size;
	size = n * (n + 1) / 2, count = 1,i = -1, j = 0, k = 1;
	while (count <= size)
	{
		while (count <= size && i < n - j - 1)
			data[++i][j] = count++;
		while (count <= size && j < n - k)
			data[i][++j] = count++;
		while (count <= size && i > k)
			data[--i][--j] = count++;
		k += 2;
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0; j <= i;j++)
			std::cout<<data[i][j]<<" ";
		std::cout<<std::endl;
	}
}

int main()
{
	int i,j,n,**data;
	std::cin>>n;
	data = new int*[n];
	for (i = 0;i < n;i++)
	{
		data[i] = new int [i + 1];
		for(j = 0;j < i + 1;j++)
			data[i][j] = 0;
	}
	draw(data,n);
	for (i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	return 0;
}
