#include <iostream>
#include <cstring>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

void refresh(int **board,int scale)
{
	memset(board,0,sizeof(int) * pow(scale,2));
}

void display(int **board,int scale)
{
	for(int i = 0;i < scale;i++)
	{
		for(int j = 0;j <scale;j++)
		{
			if(board[i][j] == 1)
				cout<<"o"<<" ";
			else
				cout<<"*"<<" ";
		}
		cout<<endl;
	}
}

bool check(int **board,int scale,int row,int col)
{
}

int queen(int **board,int scale,int &arrow)
{
	if(arrow == scale)
	{
		display(board,scale);
		return 1;
	}
	for(int i = 0;i < scale;i++)
	
}

int solution(int scale)
{
	int count,arrow;
	arrow = 0;
	int **board = new int *[scale];
	for(int i = 0;i < scale;i++)
		board[i] = new int [scale];
	count = queen(board,scale,arrow);
	for(int i = 0;i < scale;i++)
		delete [] board[i];
	delete [] board;
	return count;
}

int main()
{
	int scale;
	cout<<"input the scale of the cheese board"<<endl;
	cin>>scale;
	solution(scale);
	return 0;
}
