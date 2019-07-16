#include <iostream>
#include <random>

void barbarian(int A[],int B[],int n)
{
	if(A == nullptr || B == nullptr || n <= 0)
		return;
	int C[n],D[n];
	C[0] = D[n - 1] = 1;
	for(int i = 1;i< n;i++)
	{
		C[i] = C[i - 1] * A[i - 1];
		D[n - i - 1] = D[n - i] * A[n - i];
	}
	for(int i = 0;i < n;i++)
		B[i] = C[i] * D[i];
}

int main()
{
	std::mt19937 mt(std::random_device {}());
	int n = 5;
	int A[n],B[n];
	for(int i = 0;i < n;i++)
		A[i] = mt() % 2 + 2;
	barbarian(A,B,n);
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
