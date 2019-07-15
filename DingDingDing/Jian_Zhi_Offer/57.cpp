#include <iostream>
#include <random>
#include <stdlib.h>

int compare(const void *a,const void *b)
{
	return (*(int*)a - *(int*)b);
}

bool findsumpair(int data[],int n,int k,int &a,int &b)
{
	if(data == nullptr || n <= 0)
		return false;
	for(int i = 0,j = n - 1;i < j;)
	{
		if(data[i] + data[j] == k)
		{
			a = i;
			b = j;
			return true;
		}
		if(data[i] + data[j] > k)
			j--;
		else
			i++;
	}
	a = b = -1;
	return false;
}

int main()
{
	std::mt19937 mt(std::random_device{}());
	int n = 1000;
	int aa[n];
	for(int i = 0;i < n;i++)
		aa[i] = mt() % n;
	qsort(aa,n,sizeof(int),compare);
	int k = aa[(n >> 1) + (n >> 2)] + mt() % (n >> 1);
	int a,b;
	findsumpair(aa,n,k,a,b);
	std::cout<<aa[a]<<" + "<<aa[b]<<" = "<<k<<std::endl;
	return 0;
}
