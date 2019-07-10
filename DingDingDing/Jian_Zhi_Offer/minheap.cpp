#include "minheap.h"
#include <limits.h>
#include <iostream>

void MinHeap::allocate(int **a,int size)
{
	*a = new int [size];
	if(*a == nullptr)
		throw "out of memory";
}

void MinHeap::expantion()
{
	int *tmp;
	capacity <<= 1;
	allocate(&tmp,capacity);
	for(int i = 0;i < size;i++)
		tmp[i] = data[i];
	delete [] data;
	data = tmp;
}

MinHeap::~MinHeap()
{
	delete [] data;
	size = capacity = 0;
}

MinHeap::MinHeap()
{
	size = 0;
	capacity = N;
	allocate(&data,capacity);
}

MinHeap::MinHeap(int a[],int n)
{
	capacity = n << 1;
	allocate(&data,capacity);
	for(int i = 0;i < n;i++)
		push(a[i]);
}

int MinHeap::top()
{
	if(size == 0)
		return INT_MAX;
	return data[0];
}

void MinHeap::siftup(int start,int end)
{
	int dstone = data[start];
	int child  = start;
	int parent = (start - 1) / 2;
	while(child > end)
	{
		if(data[parent] < dstone)
			break;
		data[child] = data[parent];
		child = parent;
		parent = (parent - 1) >> 1;
	}
	data[child] = dstone;
}

void MinHeap::siftdown(int start,int end)
{
	int dstone = data[start];
	int parent = start;
	int child = (parent << 1) + 1;
	while(child <= end)
	{		
		if(child < end && data[child] > data[child + 1])
			child++;
		if(data[child] > dstone)
			break;
		data[parent] = data[child];
		parent = child;
		child = (child << 1) + 1;		
	}
	data[parent] = dstone;
}

void MinHeap::levelorder()
{
	for(int i = 0; i < size;i++)
		std::cout<<data[i]<<" ";
	std::cout<<std::endl;
}

void MinHeap::push(int a)
{
	if(size == capacity)
		expantion();
	data[size++] = a;
	siftup(size - 1,0);
}

void MinHeap::pop()
{
	if(size == 0)
		return;
	data[0] = data[--size];
	siftdown(0,size - 1);
}

bool MinHeap::isheap()
{
	if(data == nullptr || size == 0)
		return false;
	bool externsinglechild = size % 2 == 0 ? true : false;
	int lastchild = size - 1;
	int lastparent = (lastchild - 1) / 2;
	if(externsinglechild)
		if(data[lastchild] < data[lastparent])
			return false;	
	for(int i = 0;i < lastparent;i++)
		if(data[i] > data[2 * i + 1] || data[i] > data[2 * i + 2])
			return false;
	return true;
}
