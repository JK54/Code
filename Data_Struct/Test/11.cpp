#include <iostream>

int ff(int *a)
{
	return sizeof(a) / sizeof(a[0]);
}

int main()
{
	int a[] = {1,2,3,4,5};
	std::cout<<ff(a)<<std::endl;
}
