#include <iostream>
#include <limits.h>

#define MOD INT_MAX

template<int square>
struct Matrix
{
	int data[square][square];
	
	Matrix()
	{
		for(int i = 0;i < square;i++)
			for(int j = 0;j < square;j++)
			{
				if (i == j)
					data[i][j] = 1;
				else
					data[i][j] = 0;
			}
	}

	Matrix(const Matrix<square> &a)
	{
		for(int i = 0;i < square;i++)
			for(int j = 0;j < square;j++)
				data[i][j] = a.data[i][j];
	}

	Matrix<square> &operator=(const Matrix<square> &a)
	{
		for(int i = 0;i < square;i++)
			for(int j = 0;j < square;j++)
				data[i][j] = a.data[i][j];
		return *this;	
	}
	
	void disp()
	{
		for(int i = 0;i < square;i++)
		{
			for(int j = 0;j < square;j++)
				std::cout<<data[i][j]<<"\t";
			std::cout<<std::endl;
		}		
	}

	Matrix<square> multiply(Matrix<square> b)
	{
		Matrix<square> result;
		for(int i = 0;i < square;i++)
		{
			for(int j = 0;j < square;j++)
			{
				result.data[i][j] = 0;
				for(int k = 0;k < square;k++)
					result.data[i][j] += data[i][k] * b.data[k][j];
			}
		}
		return result;
	}
	Matrix<square> fast_pow(int n)
	{
		Matrix<square> result;
		Matrix<square> temp(*this);
		while(n != 0)
		{
			if(n % 2 == 1)
				result = result.multiply(temp);
			n /= 2;
			temp = temp.multiply(temp);
		}
		return result;
	}
};

//f(0) = 0,f(1) = 1...
int fib(int num)
{
	Matrix<2> as;
	as.data[0][1] = 1;
	as.data[1][0] = 1;
	as.data[1][1] = 0;
	if(num <= 0)
		return 0;
	if(num == 1 || num == 2)
		return 1;
	as = as.fast_pow(num - 1);
	return as.data[0][0];
}

int main()
{
	int n;
	std::cin>>n;
	std::cout<<fib(n)<<std::endl;
}
