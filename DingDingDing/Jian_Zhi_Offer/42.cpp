#include <iostream>
#include <limits.h>
#include <random>
#include <cstring>
int maxsumofsub(int data[],int n)
{
	if(data == nullptr || n <= 0)
		return INT_MIN;
	int sum = 0,maxsum = 0;
	int begin = 0,end = 0;
	for(int i = 0;i < n;i++)
	{
		sum += data[i];
		if(sum < 0)
			sum = 0;
		if(sum > maxsum)
		{
			maxsum = sum;
			end = i;
			for(int j = end,tmp = 0;tmp != sum && j >= 0;j--)
			{
				tmp += data[j];
				if(tmp == sum)
					begin = j;
			}
		}
	}
	std::cout<<"begin at "<<begin<<",end at "<<end<<std::endl;
	sum = 0;
	for(int i = begin;i < end;i++)
	{
		std::cout<<data[i]<<" + ";
		sum += data[i];
	}
	sum += data[end];
	std::cout<<data[end]<<" = "<<sum<<std::endl;
	return maxsum;
}

int maxsumofsub2(int data[],int n)
{
	int maxsum = INT_MIN;
	if(data == nullptr || n <= 0)
		return INT_MIN;
	int dp[n];
	std::memset(dp,0,sizeof(int) * n);
	dp[0] = data[0];
	for(int i = 1;i < n;i++)
	{
		if(dp[i - 1] < 0)
			dp[i] = data[i];
		else
			dp[i] = data[i] + dp[i - 1];
	}
	for(int i = 0;i < n;i++)
	{
		if(dp[i] > maxsum)
			maxsum = dp[i];
	}
	return maxsum;
}

int main()
{
	int n = 40;
	int *a = new int[n];
	// int a[] = {1,-2,3,10,-4,7,2,-5};
	// int n = sizeof(a) / sizeof(a[0]);
	std::random_device rd;
	std::mt19937 mt(rd());
	for(int i = 0;i < n;i++)
	{
		a[i] = mt();
		std::cout<<a[i]<<" ";
	}
	std::cout<<std::endl;
	std::cout<<maxsumofsub(a,n)<<std::endl;
	std::cout<<maxsumofsub2(a,n)<<std::endl;
	delete [] a;
}
