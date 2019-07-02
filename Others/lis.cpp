#include <iostream>
#include <cstring>
#include <limits.h>

int lis1(int a[],int size)
{
	int f[size];
	int maxsub;
	for(int i = 0;i < size;i++)
	{
		f[i] = 1;
		std::cout<<a[i]<<" ";
	}	
	std::cout<<std::endl;
	for(int i = 0;i < size;i++)
	{
		for(int j = 0;j < i;j++)
		{
			if(a[i] > a[j])
				f[i] = std::max(f[i],f[j] + 1);
		}
	}
	for(int i = 0;i < size;i++)
		std::cout<<"f["<<i<<"] = "<<f[i]<<std::endl;
	maxsub = f[0];
	for(int i = 1;i < size;i++)
		maxsub = maxsub > f[i] ? maxsub : f[i];
	return maxsub;
}

int lower_bound1(int a[],int n,int value)
{
	int low = 0,high = n,mid = n / 2;
	while(low != high)
	{
		if(a[mid] > value)
			high = mid - 1;
		else
			low = mid + 1;
		mid = (low + high) / 2;
	}
	return mid;
}

int lis2(int a[],int size)
{
	int dp[size];
	int pos;
	dp[0] = a[0];
	pos = 0;
	for(int i = 1;i < size;i++)
		dp[size] = INT_MAX;
	for(int i = 1;i < size;i++)
	{
		if(a[i] > dp[pos])
			dp[++pos] = a[i];
		else
		{
			dp[lower_bound1(dp,pos,a[i])] = a[i];
		}
	}
	for(int j = 0;j <= pos;j++)
		std::cout<<"dp["<<j<<"] = "<<dp[j]<<std::endl;	
	return pos + 1;
}

int main()
{
	int a[] = {1,5,3,4,6,9,7,8};
	int size = sizeof(a) / sizeof(a[0]);
	lis1(a,size);
	lis2(a,size);
}
