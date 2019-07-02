#include <iostream>

template<int rows,int cols>
bool solution(int (&data)[rows][cols],int value)
{
	bool found = false;
	int row = 0,col = cols - 1;
	while(row < rows && col >= 0)
	{
		int seeker = data[row][col];
		if(seeker == value)
		{
			found = true;
			break;
		}
		else if(seeker > value)
			col--;
		else
			row++;
	}
	return found;	
}

template<int rows,int cols>
bool solution2(int (&data)[rows][cols],int row,int col,int value)
{
	if(row >= rows || col >= cols)
		return false;
	if(data[row][col] == value)
		return true;
	else if(data[row][col] < value)
	{
		if(solution2<rows,cols>(data,row + 1,col,value) == true)
			return true;
		else 
			return solution2<rows,cols>(data,row,col + 1,value);
	}
	else 
		return false;
}

template<int rows,int cols>
bool solution3(int (&data)[rows][cols],bool (&visited)[rows][cols],int row,int col,int value)
{
	if(row >= rows || col >= cols)
		return false;
	if(visited[row][col] == true)
		return false;
	visited[row][col] = true;
	if(data[row][col] == value)
		return true;
	else if(data[row][col] < value)
	{
		if(solution3<rows,cols>(data,visited,row + 1,col,value) == true)
			return true;
		else 
			return solution3<rows,cols>(data,visited,row,col + 1,value);
	}
	else 
		return false;
}

int main()
{
	int data[4][4] = {{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	bool visited[4][4];
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			visited[i][j] = false;
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
		{
			std::cout<<solution3<4,4>(data,visited,0,0,data[i][j])<<std::endl;
			for(int q = 0;q < 4;q++)
				for(int w = 0;w < 4;w++)
					visited[q][w] = false;
		}
	std::cout<<solution3<4,4>(data,visited,0,0,33)<<std::endl;
}
