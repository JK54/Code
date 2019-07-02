#include <iostream>

template<int rows,int cols>
bool Path(char (matrix)[rows][cols],bool (&visited)[rows][cols],char *str,int &len,int pathlen,int row,int col)
{
	bool found = false;
	if(len == pathlen)
		return true;
	if(row >= 0 && row < rows && col >= 0 && col < cols && matrix[row][col] == str[len] && visited[row][col] == false)
	{
		++len;
		visited[row][col] = true;
		found = Path(matrix,visited,str,len,pathlen,row + 1,col) || Path(matrix,visited,str,len,pathlen,row - 1,col) || Path(matrix,visited,str,len,pathlen,row,col + 1) ||Path(matrix,visited,str,len,pathlen,row,col - 1);
		if(found == false)
		{
			--len;
			visited[row][col] = false;
		}
	}
	return found;
	// if(row < 0 || col < 0 || row >= rows || col >= cols)
		// return false;
	// if(visited[row][col] == true)
		// return false;
	// visited[row][col] = true;
	// if(matrix[row][col] == str[len])
		// len++;
	// return Path(matrix,visited,str,len,pathlen,row + 1,col) || Path(matrix,visited,str,len,pathlen,row - 1,col) || Path(matrix,visited,str,len,pathlen,row,col + 1) || Path(matrix,visited,str,len,pathlen,row,col - 1);
}

template<int rows,int cols>
bool FindPath(char (matrix)[rows][cols],char *str,int pathlen)
{
	if(matrix == nullptr || rows < 0 || cols < 0 || str == nullptr || pathlen < 0)
		return false;
	int len = 0;
	bool visited[rows][cols];
	for(int i = 0;i < rows;i++)
		for(int j = 0;j < cols;j++)
			visited[i][j] = false;
	for(int row = 0;row < rows;row++)
		for(int col = 0;col < cols;col++)
		{
			if(Path(matrix,visited,str,len,pathlen,row,col) == true)
				return true;
		}
	return false;
}

int main()
{
	char matrix[3][4] = {{'a','b','t','g'},{'c','f','c','s'},{'j','d','e','h'}};
	char str[] = "bfce";
	bool found = FindPath<3,4>(matrix,str,4);
	std::cout<<found<<std::endl;
}
