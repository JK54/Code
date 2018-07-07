#include "comm.h"

int main()
{
	std::vector<int> vec1;
	int a = vec1.at(0);
	int b = vec1[0];
	int c = vec1.front();
	auto d = vec1.begin();
	std::cout<<a<<" "<<b<<" "<<c<<" "<<*d<<std::endl;
}
