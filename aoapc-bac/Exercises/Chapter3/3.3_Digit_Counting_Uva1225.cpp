#include <iostream>
#include <cstring>

void count(int T,int *N)
{
	int i,j,tmp,**con;
	con = new int * [T];
	for(i = 0;i < T;i++)
	{
		con[i] = new int [10];
		std::memset(con[i],0,sizeof(int) * 10);
	}
	for(i = 0;i < T;i++)
	{
		for(j = 1;j <= N[i];j++)
		{
			tmp = j;
			while(tmp != 0)
			{
				con[i][tmp % 10]++;
				tmp = tmp / 10;
			}
		}
	}
	for(i = 0;i < T;i++)
	{
		for(j = 0;j < 9;j++)
			std::cout<<con[i][j]<<" ";
		std::cout<<con[i][9]<<std::endl;
		delete [] con[i];
	}
	delete [] con;
}

int main()
{
	int T,*N;
	std::cin>>T;
	N = new int [T];
	for(int i = 0;i < T;i++)
		std::cin>>N[i];
	count(T,N);
	delete [] N;
	return 0;
}
