#include <iostream>
#include "stack.h"

int main()
{
	int a[] = {1,2,3,4,5};
	int b[] = {4,5,3,2,1};
	int c[] = {4,3,5,1,2};
	int d[] = {1,2,3,4,5};
	int e[] = {3,2,1,4,5};
	int f[] = {3,1,2,4,5};
	int n = sizeof(a) / sizeof(a[0]);
	Stack aaa;
	std::cout<<aaa.poplist(a,b,n)<<std::endl;
	std::cout<<aaa.poplist(a,c,n)<<std::endl;
	std::cout<<aaa.poplist(a,d,n)<<std::endl;
	std::cout<<aaa.poplist(a,e,n)<<std::endl;
	std::cout<<aaa.poplist(a,f,n)<<std::endl;

}
