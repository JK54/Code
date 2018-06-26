#include <iostream>

void test(int **data,int n)
{
	int row,col;
	int x,y;
	for(col = 0;col < n;col++,x = 0,y = 0)
	{
		for(row = 0;row < n;row++)
		{
			if(data[row][col])
				x++;
			else
				y++;
		}
		if(x > y)
			std::cout<<(col + 1)<<" ";
	}
	std::cout<<std::endl;
}

int main()
{
	int i,j,n,**data;
	std::cin>>n;
	data = new int* [n];
	for(i = 0;i < n;i++)
		data[i] = new int [n];
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
			std::cin>>data[i][j];
	test(data,n);
	for(i = 0;i < n;i++)
		delete [] data[i];
	delete [] data;
	return 0;
}
