#include <iostream>
#include <cstring>
bool permit(int row,int col,int threshold)
{
	int sum = 0;
	while(row != 0)
	{
		sum += row % 10;
		row /= 10;
	}
	while(col != 0)
	{
		sum += col % 10;
		col /= 10;
	}
	if(sum > threshold)
		return false;
	else
		return true;
}

template<int rows,int cols>
int Walk(int matrix[rows][cols],int row,int col,int threshold)
{
	if(row >= rows || row < 0 || col >= cols || col < 0 || matrix[row][col] == 1 || permit(row,col,threshold) == false)
		return 0;
	matrix[row][col] = 1;
	int count = 1;
	count += Walk<rows,cols>(matrix,row + 1,col,threshold) + Walk<rows,cols>(matrix,row - 1,col,threshold) + Walk<rows,cols>(matrix,row,col + 1,threshold) + Walk<rows,cols>(matrix,row,col - 1,threshold);
	return count;
}

template<int rows,int cols>
int countsquare(int threshold)
{
	int matrix[rows][cols];
	memset(matrix,0,sizeof(int) * rows * cols);
	int count = Walk<rows,cols>(matrix,0,0,threshold);
	return count;
}

int main()
{
	int c = countsquare<40,40>(18);
	std::cout<<c<<std::endl;
}
