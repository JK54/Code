//解法1是DFS解法，分为递归与迭代的版本 ,时间复杂度为O(n^3)来源https://blog.csdn.net/wtyvhreal/article/details/42556199
//解法2，优化了查找冲突的过程，用S(n)的代价，预先存放一个棋盘所有的竖、撇、捺，将查找冲突时间复杂度由O(n)降低到O(1),参见https://zhuanlan.zhihu.com/p/22846106
//解法3，用位运算，将int代替16位以下的皇后问题使用的布尔数组（2*n - 1 <= 32),long处理可以处理31位皇后,采用位图的话应该可以处理更高位数的问题。
//解法4，优化了位运算，不用枚举每一列，只需要枚举每一行中还能放置的列，缩小了枚举的范围。
//解法5，更进一步优化,不使用全局参数，撇和捺的位定义修改为当前行有哪些列对应的撇或者捺已被占用

#include <iostream>
#include <cstring>
#include <cmath>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
using std::cin;
using std::cout;
using std::endl;

static int grid;
static int *board;
static int sum = 0;

static bool *shu,*pie,*na;
long long shu1,pie1,na1;

void disp()
{
	cout<<sum<<":";
	for(int i = 0;i < grid;i++)
		cout<<board[i]<<" ";
	cout<<endl;
}

bool check(int row)
{
	for(int i = 0;i < row;i++)
		if(board[row] == board[i] || row - i == abs(board[row] - board[i]))
			return false;
	return true;
}

int queens1_recursive(int row)
{
	if(row == grid)
	{
		sum++;
		// disp();
	}
	else
	{
		for(int col = 0;col < grid;col++)
		{
			board[row] = col;
			//全排列的剪枝
			if(check(row))
				queens1_recursive(row + 1);
		}
	}
	return sum;
}

int queens1_iterative()
{
	sum = 0;
	int row = 0;
	// board[row] = 0;
	board[row] = -1;
	while(row >= 0)
	{
		//当不可回溯时，所有解法都已得到
		//这一行自增代码将3种情况进行了归并处理
		//1.当计算出一种正确解法时，将最后一行的皇后右移一格，寻找新的解
		//2.当回溯到上一行时，将上一行的皇后右移一格，寻找新的解。
		//3.将新的一行（回溯的下一行或者未进行计算过的新行）列数设置为-1，这里自增过后，从第一列（下标0）开始。
		board[row]++;
		while(board[row] < grid && !check(row))
			board[row]++;
		if(board[row] < grid)
		{
			if(row == grid - 1)
			{
				sum++;
				// disp();
				// board[row]++;
			}
			else
				// board[++row] = 0;
				board[++row] = -1;
		}
		else
		{
			row--;
			// if(row >= 0)
				// board[row]++;
		}
	}
	return sum;
}

int queens2_recursive(int row)
{
	if(row == grid)
	{
		++sum;
		// disp();
	}
	else
	{
		for(int col = 0; col < grid;col++)
		{
			int shu_index = col;
			int pie_index = row + col;
			int na_index  = grid - 1 - row + col;
			if(shu[shu_index] || pie[pie_index] || na[na_index])
				continue;
			shu[shu_index] = pie[pie_index] = na[na_index] = true;
			// board[row] = col;
			queens2_recursive(row + 1);
			shu[shu_index] = pie[pie_index] = na[na_index] = false;
		}
	}
	return sum;
}

bool check(int row,int col)
{
	if(shu[col] || pie[row + col] || na[grid - 1 - row + col])
		return false;
	return true;
}

int queens2_iterative()
{
	sum = 0;
	int row = 0;
	int col;
	board[row] = -1;
	while(row >= 0)
	{
		board[row]++;
		while(board[row] < grid && !check(row,board[row]))
			board[row]++;
		if(board[row] < grid)
		{
			if(row == grid - 1)
			{
				sum++;
			}
			else
			{
				col = board[row];
				shu[col] = pie[row + col] = na[grid - 1 - row + col] = true;
				board[++row] = -1;
			}
		}
		else
		{
			row--;
			col = board[row];
			shu[col] = pie[row + col] = na[grid - 1 - row + col] = false;
		}
	}
	return sum;
}

int queens3_recursive(int row)
{
	if(row == grid)
	{
		++sum;
		// disp();
	}
	else
	{
		for(int col = 0; col < grid;col++)
		{
			int shu_index = col;
			int pie_index = row + col;
			int na_index  = grid - 1 - row + col;
			if(((shu1>>shu_index) | (pie1>>pie_index) | (na1>>na_index)) & 1)
				continue;
			shu1 ^= 1 << shu_index;
			pie1 ^= 1 << pie_index;
			na1  ^= 1 << na_index;
			// board[row] = col;
			queens3_recursive(row + 1);
			shu1 ^= 1 << shu_index;
			pie1 ^= 1 << pie_index;
			na1  ^= 1 << na_index;
		}
	}
	return sum;
	
}

int queens4_recursive(int row)
{
	if(row == grid)
	{
		++sum;
		// disp();
	}
	else
	{
		//对于每一行而言，其中每一列可以影响到的撇(row + col)的范围是row ~ row + grid - 1，捺(grid - 1- row + col)的范围是grid - 1 - row ~ 2 * grid - 2 - row
		long available = ((1 << grid) - 1) & ~(shu1 | pie1 >> row | na1 >> (grid - 1 - row));
		while(available)
		{
			//提取available最右边的1，即列号最小的可用列。
			int pos = available & -available;
			//最右1置0
			available ^= pos;
			shu1 ^= pos;
			pie1 ^= (pos << row);
			na1  ^= (pos <<(grid - 1 - row));
			//board[row] = shu1;
			queens4_recursive(row + 1);
			shu1 ^= pos;
			pie1 ^= (pos << row);
			na1  ^= (pos <<(grid - 1 - row));
		}
	}
	return sum;
}


int queens5_recursive(int row,int col,int pie2,int na2)
{
	if(row == grid)
	{
		sum++;
	}
	else
	{
		long available = ((1 << grid) - 1) & ~(col | pie2 | na2);
		while(available)
		{
			int pos = available & -available;
			available ^= pos;
			queens5_recursive(row + 1,col ^ pos,(pie2 ^ pos) >> 1,(na2 ^ pos) << 1);
		}
	}
	return sum;
}
double timecount4recur(int times,int f(int ),const char *name)
{
	struct timeval s1,s2;
	double t;
	gettimeofday(&s1,NULL);
	for(int i = 0;i < times;i++)
	{
		sum = 0;
		std::cout<<f(0)<<std::endl;
	}
	gettimeofday(&s2,NULL);
	t = (1000.0*static_cast<double>(s2.tv_sec - s1.tv_sec) + static_cast<double>(s2.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	std::cout<<name<<":"<<t<<" s"<<std::endl;
	return t;
}

double timecount4recur(int times,int f(int,int,int,int),const char *name)
{
	struct timeval s1,s2;
	double t;
	gettimeofday(&s1,NULL);
	for(int i = 0;i < times;i++)
	{
		sum = 0;
		std::cout<<f(0,0,0,0)<<std::endl;
	}
	gettimeofday(&s2,NULL);
	t = (1000.0*static_cast<double>(s2.tv_sec - s1.tv_sec) + static_cast<double>(s2.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	std::cout<<name<<":"<<t<<" s"<<std::endl;
	return t;
}

double timecount4itera(int times,int f(),const char *name)
{
	struct timeval s1,s2;
	double t;
	gettimeofday(&s1,NULL);
	for(int i = 0;i < times;i++)
	{
		std::cout<<f()<<std::endl;
	}
	gettimeofday(&s2,NULL);
	t = (1000.0*static_cast<double>(s2.tv_sec - s1.tv_sec) + static_cast<double>(s2.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	std::cout<<name<<":"<<t<<" s"<<std::endl;
	return t;
}

int main()
{
	// cout<<"input nums of queens"<<endl;
	// cin>>grid;
	grid = 15;
	board = new int [grid];
	shu = new bool [grid];
	pie = new bool [2 * grid - 1];
	na = new bool [2 * grid - 1];
	memset(board,0,sizeof(int) * grid);
	memset(shu,false,sizeof(char) * grid);
	memset(pie,false,sizeof(char) * (2 * grid - 1));
	memset(na,false,sizeof(char) * (2 * grid - 1));

	timecount4recur(1,queens4_recursive,"recursive");
	timecount4recur(1,queens5_recursive,"recursive");
	// timecount4recur(1,queens1_recursive,"recursive");
	// timecount4itera(1,queens1_iterative,"iterative");

	delete [] board;
	delete [] shu;
	delete [] pie;
	delete [] na;
	return 0;
}
