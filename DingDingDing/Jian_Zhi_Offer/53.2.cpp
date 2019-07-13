#include <iostream>
#include <random>
#include "quicksort.cpp"

int findlost(int a[],int n)
{
	if(a == nullptr || n <= 0)
		return -1;
	int left = 0,right = n - 1,mid;
	while(left <= right)
	{
		mid = (left + right) >> 1;
		if(a[mid] != mid)
		{
			//这里和53.cpp情况类似
			if(a[mid - 1] == mid - 1)
				return mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return mid;
}

int main()
{
	int n = 1000000;
	int a[n - 1];
	std::mt19937 mt(std::random_device{}());
	int lost = mt() % n;
	std::cout<<lost<<std::endl;
	for(int i = 0;i < lost;i++)
		a[i] = i;
	for(int i = lost;i < n - 1;i++)
		a[i] = i + 1;
	std::cout<<findlost(a,n)<<std::endl;
}
