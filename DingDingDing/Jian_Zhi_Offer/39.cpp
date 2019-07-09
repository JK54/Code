#include <iostream>

void swap(int &a,int &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

int partition(int data[],int left,int right)
{
	int dstone = data[left];
	int pos = left;
	for(int i = left + 1;i <= right;i++)
		if(data[i] < dstone)
			if(++pos != i)
				swap(data[pos],data[i]);
	swap(data[pos],data[left]);
	return pos;
}

void quicksort(int data[],int left,int right)
{
	if(left <right)
	{
		int pos = partition(data,left,right);
		quicksort(data,0,pos);
		quicksort(data,pos + 1,right);
	}
}

int main()
{
	int a[] = {1,5,687,3,2,45,65,8,3,2,10};
	int n = sizeof(a) / sizeof(a[0]) - 1;
	quicksort(a,0,n);
	for(int i = 0;i <= n;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
	return 0;
}
