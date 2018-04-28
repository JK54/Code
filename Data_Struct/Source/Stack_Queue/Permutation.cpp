#include <iostream>

void swap(int & l,int &r)
{
	int tmp =l;
	l = r;
	r = tmp;
}
static int k = 0;

void perm(int A[],int i,int n)
{
	if(i == 0)
	{
		++k;
		std::cout<<k<<":";
		for(int j = 0;j < n;j++)
			std::cout<<A[j];
		std::cout<<std::endl;
	}
	else
	{
		for(int j = 0 ;j <=i;j++)
		{
			swap(A[i],A[j]);
			perm(A,i - 1,n);
			swap(A[i],A[j]);
		}
	}
}


int main()
{
	int A[5];
	for(int i = 1;i<6;i++)
		A[i - 1] = i;
	perm(A,4,5);
}
