#include <iostream>
#include <cstring>
#include <cmath>

//数组下标从1开始算
//状态转移方程：dice(c,n) = dice(c - 1,n - 1) + dice(c - 1,n - 2) + ... + dice(c - 1,n - 6),c是骰子数，n是点数和
void dice(int num,int side)
{
	if(num <= 0 || side <= 0)
		return;
	int **dp;
	double totalcount,rate,sum,ratesum;
	dp = new int *[num + 1];
	dp[0] = nullptr;
	for(int i = 1;i <= num;i++)
	{
		dp[i] = new int [i * side + 1];
		std::memset(dp[i],0,sizeof(int) * (i * side + 1));
	}
	for(int i = 1;i <= 6;i++)
		dp[1][i] = 1;
	for(int i = 2;i <= num;i++)
	{
		for(int j = i;j <= i * side;j++)
		{
			if(j > (i - 1) *side)
				for(int k = j - 6;k <= (i - 1) *side;k++)
					dp[i][j] += dp[i - 1][k];
			else
				for(int k = j - 1;k > 0 && k >= j - 6;k--)
					dp[i][j] += dp[i - 1][k];
		}
	}
	totalcount = pow(side,num);
	ratesum = sum = 0;
	for(int i = num;i <= num * side;i++)
	{
		sum += dp[num][i];
		rate = dp[num][i] / totalcount;
		ratesum += rate;
		std::cout<<i<<" : "<<dp[num][i]<<" / "<<totalcount<<" , "<<rate<<std::endl;
	}
	std::cout<<ratesum<<std::endl;
	std::cout<<"count : "<<sum<<",calculated : "<<totalcount<<std::endl;
	for(int i = 1;i <= num;i++)
		delete [] dp[i];
	delete [] dp;
}

int main()
{
	int num = 10;
	int side = 6;
	dice(num,side);
}
