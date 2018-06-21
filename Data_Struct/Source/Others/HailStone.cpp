#include "include/sys_comm.h"

void hailstone(int n,std::vector<int>&result)
{
	while(1 < n)
	{
		n = (n % 2 == 0)?n/2:3*n+1;
		result.push_back(n);
	}
	if(n == 1)
		result.push_back(n);
}

void print(std::vector<int> &a)
{
	for(auto i:a)
		std::cout<<i<<" ";
	std::cout<<std::endl;
}

int main()
{
	std::vector<int> aaa;
	hailstone(502665165,aaa);
	print(aaa);
}
