#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
bool input(char block[][15],int &r,int &c,int &count)
{
	int i;
	if(scanf("%d",&r) && r == 0)
		return false;
	scanf("%d",&c);
	getchar();
	for(i = 0;i < r;i++)
		fgets(block[i],15,stdin);
	count++;
	return true;
}

void output(char block[][15],int r,int c,int count)
{
	int i,j,k;
	int list[15][15];
	for(i = 0,k = 1;i < r;i++)
		for(j = 0;j < c;j++)
			if(block[i][j] != '*' && (i == 0 || j == 0 || block[i - 1][j] == '*' || block[i][j - 1] == '*'))
				list[i][j] = k++;
			else
				list[i][j] = 0;
	if(count > 1)
		std::cout<<'\n';
	std::cout<<"puzzle #"<<count<<":"<<'\n'<<"Across"<<'\n';
	for(i = 0;i < r;i++)
		for(j = 0;j < c;j++)
			if(list[i][j])
			{
				std::cout<<std::setw(3)<<list[i][j]<<".";
				while(j < c && block[i][j] != '*')
					std::cout<<block[i][j++];
				std::cout<<'\n';
			}
	std::cout<<"Down"<<'\n';
	for(i = 0;i < r;i++)
		for(j = 0;j < c;j++)
			if(list[i][j] && (i == 0 || block[i - 1][j] == '*'))
			{
				std::cout<<std::setw(3)<<list[i][j]<<".";
				for(k = i;block[k][j] != '*' && k < r;k++)
					std::cout<<block[k][j];
				std::cout<<'\n';
			}
}
int main()
{
	std::ios::sync_with_stdio(false);
	int r,c,count = 0;
	char block[15][15];
	while(input(block,r,c,count))
		output(block,r,c,count);
	return 0;
}
