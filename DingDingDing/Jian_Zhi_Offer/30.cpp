#include <iostream>
#include "stack.h"

int main()
{
	int a[] = {9,8,7,6,1,2,3,4};
	int size = sizeof(a) / sizeof(a[0]);
	Stack aaa;
	for(int i = 0;i < size;i++)
	{
		aaa.push(a[i]);
		std::cout<<aaa.min();
	}
	std::cout<<std::endl;
	for(int i = 0;i < size;i++)
	{
		// try
		// {
		std::cout<<aaa.min();
		aaa.pop();
		// }		
   /*      catch(const char *msg) */
		// {
			// std::cout<<msg;	
		/* } */
		
	}
	return 0;
}
