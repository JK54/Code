#include "comm.h"

int main()
{
	std::list<int> list1{ 1, 2,45,234,6587,2342,678,234,567,243, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	std::deque<int> even,odd;
	for(std::list<int>::const_iterator iter1 = list1.cbegin();iter1 != list1.cend();++iter1)
	{
		if(*iter1 %2 == 0)
			even.emplace_back(*iter1);
		else
			odd.emplace_back(*iter1);
	}
	for(auto i:even)
		std::cout<<i<<" ";
	std::cout<<std::endl;;
	for(auto i:odd)
		std::cout<<i<<" ";
	std::cout<<std::endl;
	return 0;
}
