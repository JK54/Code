#include <iostream>

int count1(int n)
{
	int count = 0;
	while(n != 0)
	{
		count++;
		n = (n - 1) & n;
	}
	return count;
}

int main()
{
	int n;
	std::cin>>n;
	std::cout<<count1(n)<<std::endl;
}
