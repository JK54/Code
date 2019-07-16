#include <iostream>
#include <stdlib.h>
#include <random>

void drawcards(int a[],int nums,int size)
{
	std::mt19937 mt(std::random_device {}());
	for(int i = 0;i < nums;i++)
		a[i] = mt() % size;
}

int compare(const void *a,const void *b)
{
	return *(int *)a - *(int *)b;
}

void disp(int cards[],int nums)
{
	for(int i = 0;i < nums;i++)
		std::cout<<cards[i]<<" ";
	std::cout<<std::endl;
}

bool isstraight(int a[],int n)
{
	if(a == nullptr || n <= 4)
		return false;
	qsort(a,n,sizeof(int),compare);
	int ghostnum = 0,gap = 0,index = 0;
	while(index < n && a[index] == 0)
		ghostnum++,index++;
	while(index < n - 1)
	{
		if(a[index] == a[index + 1])
			return false;
		gap += a[index + 1] - a[index] - 1;
		index++;
	}
	if(ghostnum > gap)
		return true;
	return false;
}

int main()
{
	int nums = 5;
	int size = 14;
	int cards[nums];
	drawcards(cards,nums,size);
	while(!isstraight(cards,nums))
		drawcards(cards,nums,size);
	disp(cards,nums);
}
