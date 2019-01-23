#include "include/sys_comm.h"

using namespace std;
#define n 12
#define b 5

int main()
{
	int array[n][n] = {{0}};
	for(int i = 1;i <= n; ++i)
	{
		if( i <= b)
		{
			for(int j = 0; j < b + i; ++j)
				array[i - 1][j] = 1;
		}
		 if( i > b && i < n - b + 1)
			 for(int j = i - n + b + 1; j < b + i; ++j)
				 array[i - 1][j] = 1;
		if( i <= n && i >= n - b + 1)
		{
			for(int j = i - n + b + 1; j <= n - 1; ++j)
				array[i - 1][j] = 1;
		}
	}
	for(int i = 0; i < n; ++i)
	{
		for(auto j : array[i])
			cout<<j<<" ";
		cout<<endl;
	}
}
