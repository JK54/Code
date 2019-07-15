#include <iostream>
#include <fstream>
#include "quicksort.cpp"
#include <random>
#include <cstring>
#include <unordered_map>
#include <sys/time.h>
void randomz(int a[],int n)
{
	std::mt19937 mt(std::random_device {}());
	for(int i = 0;i < n / 2;i++)
		std::swap(a[mt() % n],a[mt() % n]);
}

void init(int a[],int n)
{
	std::mt19937 mt(std::random_device{}());
	int dspos = (mt() % (n / 3)) * 3;
	int num = (mt() % 2 == 1 ? 1 : -1)*(mt() % n);
	for(int i = 0;i < n;)
	{
		num += mt() % 10 + 1;
		if(i != dspos)
		{
			for(int j = 0;j < 3;j++)
				a[i + j] = num;
			i += 3;
		}
		else
		{
			a[i] = num;
			i++;
		}
	}
	randomz(a,n);
}

int sortfind(int a[],int n)
{
	if(a == nullptr || n <= 0)
		return 0;	
	quicksort<int>(a,0,n - 1);
	int result = 0;
	for(int i = 0;i < n;i += 3)
	{
		if(i == n - 1 || a[i] != a[i + 1])
		{
			result = a[i];
			break;
		}
	}
	return result;
}

int hashfind(int a[],int n)
{
	if(a == nullptr || n <= 0)
		return 0;
	std::unordered_map<int,int> nums;
	for(int i = 0;i < n;i++)
		++nums[a[i]];
	for(std::unordered_map<int,int>::iterator p = nums.begin();p != nums.end();++p)
	{
		if(p->second == 1)
			return p->first;
	}
	return 0;
}

int addfind(int a[],int n)
{
	if(a == nullptr || n <= 0)
		return 0;
	int bitsum[32];
	int bitmask[32];
	std::memset(bitsum,0,sizeof(int) * 32);
	for(int i = 0,mask = 1;i < 32;i++,mask <<= 1)
		bitmask[i] = mask;
	for(int i = 0;i < n;i++)
		for(int j = 31;j >= 0;j--)
		{
			if(a[i] & bitmask[j])
				bitsum[j] += 1;
		}
	int result = 0;
	for(int i = 0;i < 32;i++)
		result += (bitsum[i] % 3) << i;
	return result;
}

void timecount(int f(int *,int),int a[],int n)
{
	struct timeval s1,s2;
	double t;
	gettimeofday(&s1,NULL);
	std::cout<<f(a,n)<<std::endl;
	gettimeofday(&s2,NULL);
	t = (1000.0*static_cast<double>(s2.tv_sec - s1.tv_sec) + static_cast<double>(s2.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	std::cout<<t<<" s"<<std::endl;
}

int main()
{
	int n = 10000000;
	int *data = new int[n];
	init(data,n);
	timecount(sortfind,data,n);
	timecount(hashfind,data,n);
	timecount(addfind,data,n);
	delete [] data;
	return 0;
}
