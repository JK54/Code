#include <iostream>

#define SIZE 10
bool isprime(int n)
{
	if(n == 1)
		return false;
	for(int i = 2;i < n;i++)
		if(n % i == 0)
			return false;
	return true;
}
int sum(int n)
{
	int sum = 0;
	for(int i = 2;i <= n;i++)
		if(isprime(i))
			sum += i;
	return sum;
}

int main()
{
	int n[SIZE];
	int i,j,tmp;
	for(i = 0;i < SIZE;i++)
	{
		std::cin>>tmp;
		if(tmp != 0)
			n[i] = tmp;
		else
			break;
	}
	j = --i;
	while(j >= 0)
	{
		n[j] = sum(n[j]);
		j--;
	}
	for(j = 0;j <= i;j++)
		std::cout<<n[j]<<std::endl;
	return 0;
}
