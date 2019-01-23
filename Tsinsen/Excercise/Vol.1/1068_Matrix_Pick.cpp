#include <iostream>

void mpick(int **data,bool **picked,int *result,int row,int col)
{
	int i,j,k,size,count;
	size = row * col;
	i = -1,j = 0,k = 0,count = 0;
	while(count < size)
	{
		while(count < size && i < row - k - 1)
		{
			result[count++] = data[++i][j];
			picked[i][j] = true;
		}
		while(count < size && j < col - k - 1)
		{
			result[count++] = data[i][++j];
			picked[i][j] = true;
		}
		while(count < size && i > k)
		{
			result[count++] = data[--i][j];
			picked[i][j] = true;
		}
		while(count < size && j > k + 1)
		{
			result[count++] = data[i][--j];
			picked[i][j] = true;
		}
		k++;
	}
	for(i = 0;i < size;i++)
		std::cout<<result[i]<<" ";
	std::cout<<std::endl;
}

int main()
{
	int row,col,**data,*result;
	bool **picked;
	int i,j;
	std::cin>>row>>col;
	data = new int *[row];
	picked = new bool *[row];
	result = new int [row * col];
	for(i = 0;i < row;i++)
	{
		data[i] = new int [col];
		picked[i] = new bool [col];
		for(j = 0;j < col;j++)
		{
			std::cin>>data[i][j];
			picked[i][j] = false;
			result[i * col + j] = 0;
		}
	}
	mpick(data,picked,result,row,col);
	for(i = 0;i < row;i++)
	{
		delete [] data[i];
		delete [] picked[i];
	}
	delete [] data;
	delete [] picked;
	delete [] result;
	return 0;
}
