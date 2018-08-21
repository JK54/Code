#include "../Include/BIT.hpp"

int main()
{
	BIT<int> aaa;
	aaa.PrintSize();
	for(int i = 1;i <= 10;i++)
		aaa.Insert(i);
	aaa.PrintSize();
	std::cout<<aaa.Sum(11)<<std::endl;
	aaa.Modify(5,123);
	aaa.PrintSize();
	std::cout<<aaa.Sum(12)<<std::endl;
	aaa.Modify(5,113);
	aaa.PrintSize();
	std::cout<<aaa.Sum(12)<<std::endl;
}
