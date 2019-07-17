#include <iostream>
#include <random>

void barbarian(int A[],int B[],int n1,int n2)
{
	if(A == nullptr || B == nullptr || n1 != n2 || n1 < 2)
		return;
	B[0] = 1;
	for(int i = 1;i< n1;i++)
		B[i] = B[i - 1] * A[i - 1];
	int tmp = 1;
	for(int i = n1 - 2;i >= 0;i--)
	{
		tmp *= A[i + 1];
		B[i] *= tmp;
	}
}

int main()
{
	std::mt19937 mt(std::random_device {}());
	int n = 5;
	int A[n],B[n];
	for(int i = 0;i < n;i++)
		A[i] = mt() % 2 + 2;
	barbarian(A,B,n,n);
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			if(i == j)
				std::cout<<B[j]<<" ";
			else
				std::cout<<A[j]<<" ";
		}
		std::cout<<std::endl;
	}
	return 0;
}
