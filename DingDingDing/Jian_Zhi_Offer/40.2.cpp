#include <iostream>
#include "maxheap.h"
#include "quicksort.cpp"
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	int a[20];
	int k = 5;
	for(int i = 0; i < 20;i++)
		a[i] = mt() % 100000;
	MaxHeap aaa;
	for(int i = 0;i < 20;i++)
	{
		if(aaa.size < k)
			aaa.push(a[i]);
		else
		{
			if(aaa.top() > a[i])
			{
				aaa.pop();
				aaa.push(a[i]);
			}
		}
	}
	quicksort(a,0,19);
	for(int i = 0;i < 20;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
	aaa.levelorder();
}
