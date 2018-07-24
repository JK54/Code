#include <iostream>
#define M 55
#define N 1080
void input(std::istream &is,char data[][N],int &m,int &n)
{
	int i,j;
	is>>m>>n;
	for(i = 0;i < m;i++)
		for(j = 0;j < n;j++)
			is>>data[i][j];
}

void output(char data[][N],int m,int n)
{
	int i,j,sum,max,count[4];
	char ref[4] = {'A','C','G','T'};
	sum = 0;
	for(j = 0;j < n;j++)
	{
		for(i = 0;i < 4;i++)
			count[i] = 0;
		for(i = 0;i < m;i++)
		{
			if(data[i][j] == ref[0])
				count[0]++;
			else if(data[i][j] == ref[1])
				count[1]++;
			else if(data[i][j] == ref[2])
				count[2]++;
			else
				count[3]++;
		}
		for(i = 1,max = 0;i < 4;i++)
			if(count[max] < count[i])
				max = i;
		std::cout<<ref[max];
		sum += count[0] + count[1] + count[2] + count[3] - count[max];
	}
	std::cout<<'\n'<<sum<<'\n';
}
int main()
{
	std::ios::sync_with_stdio(false);
	char data[M][N];
	int k,m,n;
	std::cin>>k;
	while(k > 0)
	{
		input(std::cin,data,m,n);
		output(data,m,n);
		k--;
	}
}
