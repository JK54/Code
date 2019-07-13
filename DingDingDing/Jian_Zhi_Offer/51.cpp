#include <iostream>
#include <random>
#include <limits.h>

int inverse_pair(int data[],int n)
{
	int inversecount = 0;
	for(int i = 0;i < n;i++)
		for(int j = i + 1;j < n;j++)
			if(data[i] > data[j])
				inversecount++;
	return inversecount;
}

int merge(int &count,int data[],int left,int mid,int right)
{
	if(left == right)
		return 0;
	int copy[right - left + 1];
	int i,j,k;
	i = mid,j = right,k = right - left;
	while(i >= left && j > mid)
	{
		if(data[i] > data[j])
		{
			count += j - mid;
			copy[k--] = data[i--];
		}	
		else
			copy[k--] = data[j--];
	}
	while(i >= left)
		copy[k--] = data[i--];
	while(j > mid)
		copy[k--] = data[j--];
	for(int l = left;l <= right;l++)
		data[l] = copy[++k];
	return count;
}

int mergesort(int data[],int n)
{
	if(data == nullptr || n <= 0)
		return 0;
	int size = 1;
	int count = 0;
	while(size < n)
	{
		int left = 0;
		while(left + size < n)
		{
			int mid = left + size - 1;
			int right = mid + size;
			if(right > n)
				right = n - 1;
			merge(count,data,left,mid,right);
			left = right + 1;
		}
		size <<= 1;
	}
	return count;
}

int inverse_pair2(int data[],int n)
{
	int count = mergesort(data,n);
	return count;
}

int main()
{
	std::mt19937 mt(std::random_device{}());
	int n = 10000;
	int data[n];
	for(int i = 0;i < n;i++)
		data[i] = mt() % INT_MAX;
	std::cout<<inverse_pair(data,n)<<std::endl;
	std::cout<<inverse_pair2(data,n)<<std::endl;
}
