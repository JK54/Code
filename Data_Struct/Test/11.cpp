#include <set>
#include <iostream>

int main()
{
	std::multiset<int> aaa;
	int a[] = {7,6,4,2,3,6345,23,12,12,234,3456,756};
	for(int i = 0;i < (int)(sizeof(a) / sizeof(a[0]));i++)
		aaa.insert(a[i]);
	std::multiset<int>::reverse_iterator p = aaa.rbegin();
	std::cout<<*p<<std::endl;
}
