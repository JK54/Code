#include <iostream>

int main()
{
	int num;
	std::cin>>num;
	long long seq[num];
	seq[0] = seq[1] = 1;
	for(int i = 2;i < num;i++)
	{
		seq[i] = seq[i - 1] + seq[i - 2];
	}
	for(int i = 0;i < num;i++)
	{
		std::cout<<seq[i]<<'\t';
	}
	std::cout<<std::endl;
}
