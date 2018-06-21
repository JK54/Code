#include <iostream>

void Queen(int G[],int i)
{
	int j,k,conflict;
	if(i == 8)
	{
		for(j = 0;j<8;j++)
		std::cout<<j<<" row, "<<G[j]<<" column"<<std::endl;
		return;
	}
	for(j = 0 ; j < 8;j++)
	{
		conflict = 0;
		for(k = 0;k <i;k++)
		{
			if(j == G[k]||i - k == j - G[k]||i - k == G[k] - j)
				conflict = 1;
			if(!conflict)
			{
				G[i] = j;
				Queen(G,i+1);
			}
		}
	}
}

int main()
{
	int G[8];
	Queen(G,1);
}
