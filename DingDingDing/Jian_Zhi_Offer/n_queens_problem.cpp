#include <iostream>
#include <cstring>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

static int grid;
static int *board;

void disp(int i)
{
	cout<<"第"<<i<<"个解法:"<<endl;
	for(int i = 0;i < grid;i++)
	{
		for(int j = 0;j < grid;j++)
		{
			if(j == board[i])
				cout<<"o ";
			else
				cout<<"* ";
		}
		cout<<endl;
	}
}

bool check(int row)
{
	for(int i = 0;i < row;i++)
		if(board[row] == board[i] || row - i == abs(board[row] - board[i]))
			return false;
	return true;
}

int solution1()
{
}

int main()
{
	cout<<"input nums of queens"<<endl;
	cin>>grid;
	board = new int [grid];
	memset(board,0,sizeof(int) * grid);
	solution1();
	delete [] board;
	return 0;
}
