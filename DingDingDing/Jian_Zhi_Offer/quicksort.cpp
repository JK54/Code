#include <iostream>

void swap(int &a,int &b)
{
	int c = a;
	a = b;
	b = c;
}

int partition(int data[],int left,int right)
{
	int dstone = data[left];
	int pos = left;
	for(int i = left + 1;i <= right;i++)
	{
		if(data[i] < dstone)
			if(++pos != i)
				swap(data[pos],data[i]);
	}
	swap(data[left],data[pos]);
	return pos;
}

void quicksort(int data[],int left,int right)
{
	if(left < right)
	{
		int pos = partition(data,left,right);
		quicksort(data,0,pos);
		quicksort(data,pos + 1,right);
	}
}

int main()
{
	int a[] = {13,8,9,10,103,3,0,5,1,2,7,12,0,11};
	int size = sizeof(a)/sizeof(a[0]) - 1;
	quicksort(a,0,size);
	for(int i = 0;i <= size;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}
