#include <iostream>
#include "quicksort.cpp"

void findks(int data[],int len,int k)
{
	if(k < 0 || k > len)
		return;
	int begin = 0,end = len - 1;
	int mid = partition(data,begin,end);
	while(mid != k)
	{
		if(mid > k)
			end = mid - 1;
		else
			begin = mid + 1;
		mid = partition(data,begin,end);
	}
	for(int i = 0;i < mid;i++)
		std::cout<<data[i]<<" ";
	std::cout<<std::endl;
}

int main()
{
	int a[] = {1,2,3,6,87,9,4,2,234,867,234,12,345,6578,67,3124,2345,43526,4567,3};
	findks(a,sizeof(a)/sizeof(a[0]),8);
}
