#include <iostream>

bool isprime(int n)
{
	if(n == 0 || n == 1)
		return false;
	for(int i = 2; i < n; i++)
		if(n % i == 0)
			return false;
	return true;
}

int main()
{
	int i,n;
	std::cin>>n;
	i = 0;
	if(isprime(n))
		for(i = n + 1; !isprime(i); i++);
	std::cout<<i<<std::endl;
}
