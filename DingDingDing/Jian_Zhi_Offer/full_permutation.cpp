#include <iostream>
#include "quicksort.cpp"

template<typename T>
void permutation1(T a[],int start,int end,int &count)
{
	if(a == nullptr)
		return;
	if(start > end)
	{
		std::cout<<++count<<":";
		for(int i = 0;i <= end;i++)
			std::cout<<a[i]<<" ";
		std::cout<<std::endl;
	}
	for(int i = start;i <= end;i++)
	{
		swap<T>(a[start],a[i]);
		permutation1(a,start + 1,end,count);
		swap<T>(a[start],a[i]);
	}
}

template<typename T>
void reverse(T a[],int start,int end)
{
	while(start < end)
	{
		swap(a[start],a[end]);
		start++,end--;
	}
}

template<typename T>
void permutation2(T a[],int endindex)
{
	if(a == nullptr || endindex < 0)
		return;
	quicksort<T>(a,0,endindex);
	int count = 0;
	std::cout<<++count<<":";
	disp(a,endindex);
	while(1)
	{
		int firstraisepair;
		for(firstraisepair = endindex - 1;firstraisepair >= 0;firstraisepair--)
			if(a[firstraisepair] < a[firstraisepair + 1])
				break;
		if(firstraisepair < 0)
			break;
		for(int i = endindex;i > firstraisepair;i--)
			if(a[i] > a[firstraisepair])
			{
				swap(a[i],a[firstraisepair]);
				break;
			}
		reverse(a,firstraisepair + 1,endindex);
		std::cout<<++count<<":";
		disp(a,endindex);
	}
}

int main()
{
	char a[] = "abcdfe";
	int b[] = {1,2,5,4,3,6};
	int s1,s2;
	s1 = sizeof(a) / sizeof(a[0]) - 2;
	s2 = sizeof(b) / sizeof(b[0]) - 1;
	permutation2<int>(b,s2);
	permutation2<char>(a,s1);
}
