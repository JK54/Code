#include "minheap.h"
#include <random>
#include <iostream>

int main()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	int a[31];
	MinHeap aaa;
	for(int i = 0;i < 31;i++)
	{
		aaa.push(mt() % 1000086 );
		std::cout<<aaa.isheap()<<std::endl;
	}
	for(int i = 0;i < 31;i++)
	{
		a[i] = aaa.top();
		aaa.pop();
		std::cout<<aaa.isheap()<<std::endl;
	}
	for(int i = 0;i < 31;i++)
	{
		std::cout<<a[i]<<" ";
	}
	std::cout<<std::endl;
}
