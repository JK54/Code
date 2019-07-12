#include <iostream>
#include <limits.h>

int getmaxgift(int **board,int rows,int cols)
{
	if(board == nullptr || rows <= 0 || cols <= 0)
		return INT_MIN;
	int **record = new int *[rows];
	int maxvalue;
	for(int i = 0;i < rows;i++)
		record[i] = new int [cols];
	for(int i = 0;i < rows;i++)
	{
		for(int j = 0;j < cols;j++)
		{
			int left = 0;
			int up = 0;
			if(i > 0)
				up = record[i - 1][j];
			if(j > 0)
				left = record[i][j - 1];
			record[i][j] = std::max(up,left) + board[i][j];
		}
	}
	maxvalue = record[rows - 1][cols - 1];
	for(int i = 0;i < rows;i++)
		delete [] record[i];
	delete [] record;
	return maxvalue;
}

int getmaxgift2(int *board,int rows,int cols)
{
	if(board == nullptr || rows <= 0 || cols <= 0)	
		return INT_MIN;
	int record[cols];
	for(int i = 0;i < rows;i++)
		for(int j = 0;j < cols;j++)
		{
			int left = 0;
			int up = 0;
			if(i > 0)
				up = record[j];
			if(j > 0)
				left = record[j - 1];
			record[j] = std::max(up,left) + board[i * cols + j];
		}
	return record[cols - 1];
}

int main()
{
	int a[] = {1,10,3,8,12,2,9,6,5,7,4,11,3,7,16,5};
	int rows = 4,cols = 4;
	int **board = new int* [rows];
	for(int i = 0,k = 0;i < rows;i++)
	{
		board[i] = new int [cols];
		for(int j = 0;j < cols;j++)
			board[i][j] = a[k++];
	}
	std::cout<<getmaxgift2(a,rows,cols)<<std::endl;
	for(int i = 0;i < rows;i++)
		delete [] board[i];
	delete [] board;
}
