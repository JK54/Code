#include <iostream>
#include <random>
#include "quicksort.cpp"

int binsearch(int a[],int n,int k)
{
	int left = 0,right = n,mid;
	while(left <= right)
	{
		mid = (left + right) >> 1;
		if(a[mid] == k)
			return mid;
		if(a[mid] > k)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int findmatch(int a[],int n)
{
	if(a == nullptr || n <= 0)
		return -1;
	int left = 0,right = n - 1,mid;
	while(left <= right)
	{
		 mid = (left + right) >> 1;
		 if(a[mid] == mid)
			 return mid;
		if(a[mid] > mid)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int main()
{
	int n = 1500;
	int a[n];
	std::mt19937 mt(std::random_device {}());
	for(int i = 1;i < n;i++)
	{
		int num = (mt() % n) ;
		while(binsearch(a,i,num) != -1)
			num = (mt() % n) ;
		a[i] = num;
	}
	quicksort(a,0,n - 1);
	int index = findmatch(a,n);
	std::cout<<index<<std::endl;
}
