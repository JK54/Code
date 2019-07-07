#include <iostream>

void printnum(int num,int count,int size)
{
	std::cout<<num;
	if(count != size)
		std::cout<<",";
	std::cout<<std::flush;
}

void printmatrixclockwise(int **matrix,int rows,int cols)
{
	if(matrix == nullptr || rows <= 0 || cols <= 0)
		return;
	int count = 0;
	int size = rows * cols;
	int row = 0,col = 0,round = 0;
	while(count < size)
	{
		while(count < size && col < cols - round)
			printnum(matrix[row][col++],++count,size);
		++row;
		--col;
		while(count < size && row < rows - round)
			printnum(matrix[row++][col],++count,size);
		--row;
		--col;
		while(count < size && col >= round)
			printnum(matrix[row][col--],++count,size);
		--row;
		++col;
		while(count < size && row >= round + 1)
			printnum(matrix[row--][col],++count,size);
		++row;
		++col;
		++round;
	}
	std::cout<<std::endl;
}

int main()
{
	int row,col;
	std::cin>>row>>col;
	int **matrix = new int *[row];
	std::cout<<std::endl;
	std::cout<<std::endl;
	for(int i = 0;i < row;i++)
	{
		matrix[i] = new int [col];
		for(int j = 0; j < col;j++)
			matrix[i][j] = i * col + j + 1;
	}

	for(int i = 0;i < row;i++)
	{
		for(int j = 0;j < col;j++)
			std::cout<<matrix[i][j]<<'\t';
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	std::cout<<std::endl;
	printmatrixclockwise(matrix,row,col);
	for(int i = 0;i < row;i++)
		delete [] matrix[i];
	delete [] matrix;
	return 0;
}
