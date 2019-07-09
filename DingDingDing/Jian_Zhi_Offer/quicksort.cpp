#include <iostream>

template<typename T>
void swap(T &a,T &b)
{
	T c = a;
	a = b;
	b = c;
}

template<typename T>
void disp(T a[],int n)
{
	for(int i = 0;i <= n;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}

template<typename T>
int partition(T data[],int left,int right)
{
	T dstone = data[left];
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

template<typename T>
void quicksort(T data[],int left,int right)
{
	if(left < right)
	{
		int pos = partition(data,left,right);
		quicksort(data,0,pos);
		quicksort(data,pos + 1,right);
	}
}

/* int main() */
// {
	// int a[] = {13,8,9,10,103,3,0,5,1,2,7,12,0,11};
	// int size = sizeof(a)/sizeof(a[0]) - 1;
	// quicksort<int>(a,0,size);
	// for(int i = 0;i <= size;i++)
		// std::cout<<a[i]<<" ";
	// std::cout<<std::endl;
/* } */
