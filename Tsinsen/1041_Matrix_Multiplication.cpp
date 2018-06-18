#include <iostream>

void value(int **source,int **dest,int n)
{
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
			dest[i][j] = source[i][j];
	}
}
void value(int **dest,int vle,int n)
{
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
			dest[i][j] = vle;
	}
}
void muti(int **data,int **result,int n,int m)
{
	int i,j,k,l;
	int **tmp = new int* [n];
	for(i = 0;i < n;i++)
	{
		tmp[i] = new int[n];
		for(j = 0;j < n;j++)
			tmp[i][j] = 0;
	}
	value(data,result,n);
	for(l = 1;l < m;l++)
	{
		for(i = 0;i < n;i++)
			for(j = 0;j < n;j++)
				for(k = 0;k < n;k++)
				{
					tmp[i][j] += result[i][k] * data[k][j];
				}
		value(tmp,result,n);
		value(tmp,0,n);
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < n;j++)
			std::cout<<result[i][j]<<" ";
		std::cout<<std::endl;
	}
	for(i = 0;i < n;i++)
		delete [] tmp[i];
	delete [] tmp;
}

int main()
{
	int n,m,i,j;
	int **data,**result;
	std::cin>>n>>m;
	data = new int*[n];
	result = new int*[n];
	for(i = 0;i < n;i++)
	{
		data[i] = new int[n];
		result[i] = new int[n];
	}
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			std::cin>>data[i][j];
	muti(data,result,n,m);
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	for(i = 0;i < n;i++)
		delete [] result[i];
	delete [] result;
	return 0;
}
