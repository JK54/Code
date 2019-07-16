#include <iostream>

int Add(int num1,int num2)
{
	int sum,carry;
	while(num2 != 0)
	{
		sum = num1 ^ num2;
		carry = (num1 & num2) << 1;
		num1 = sum;
		num2 = carry;
	}
	return num1;
}

int main()
{
	int n1,n2;
	n1 = 10;
	n2 = 101;
	std::cout<<Add(n1,n2)<<std::endl;
}
