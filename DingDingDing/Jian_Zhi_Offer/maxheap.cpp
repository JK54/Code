#include <iostream>
#include "maxheap.h"
#include <limits.h>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;


void MaxHeap::allocate(int **a,int size)
{
	*a = new int [size];
	if(data == nullptr)
	{
		cerr<<"unable to allocate memory"<<endl;
		throw "unable to allocate memory";
	}
}

MaxHeap::MaxHeap()
{
	allocate(&data,N);
	capacity = N;
	size = 0;
}

MaxHeap::MaxHeap(int a[],int n)
{
	allocate(&data,2 * n);
	size = 0;
	capacity = 2 * n;
	for(int i = 0;i < n;i++)
		push(a[i]);
}

MaxHeap::~MaxHeap()
{
	delete [] data;
	data = nullptr;
	size = capacity = 0;
}

void MaxHeap::expantion()
{
	if(size == capacity)
		capacity *= 2;
	int *tmp;
	allocate(&tmp,capacity);
	for(int i = 0;i < size;i++)
		tmp[i] = data[i];
	delete [] data;
	data = tmp;
}

void MaxHeap::siftup(int bottom,int topp)
{
	int dstone = data[bottom];
	int child = bottom;
	int parent = (child - 1) / 2;
	while(child > topp)
	{
		if(data[parent] > dstone)
			break;
		data[child] = data[parent];
		child = parent;
		parent = (parent - 1) / 2;
	}
	data[child] = dstone;
}

void MaxHeap::siftdown(int topp,int bottom)
{
	int dstone = data[topp];
	int parent = topp;
	int child = parent * 2 + 1;
	while(child <= bottom)
	{
		if(child < bottom && data[child] < data[child + 1])
			child++;
		if(dstone > data[child])
			break;
		data[parent] = data[child];
		parent = child;
		child = 2 * child + 1;
	}
	data[parent] = dstone;
}

int MaxHeap::top()
{
	if(size == 0)
		return INT_MIN;
	return data[0];
}

void MaxHeap::push(int ori)
{
	if(size == capacity)
		expantion();
	data[size++] = ori;
	siftup(size - 1,0);
}

void MaxHeap::pop()
{
	if(size == 0)
		return;
	data[0] = data[--size];
	siftdown(0,size - 1);
}

bool MaxHeap::isheap()
  {
      int n = size;
      if(n % 2 == 0)
      {
          if(data[n / 2 - 1] < data[n - 1])
          {
              std::cout<<"Not Heap1!"<<std::endl;
              return false;
          }
          for(int i = 0;i < n / 2 - 1;i++)
          {
              if(data[i] < data[2 * i + 1] || data[i] < data[2 * i + 2])
              {
                  std::cout<<"Not Heap2!"<<std::endl;
                  return false;
              }
          }
      }
      else
      {
          for(int i = 0;i < n / 2;i++)
          {
              if(data[i] < data[2 * i + 1] || data[i] < data[2 * i + 2])
              {
                  std::cout<<"Not Heap3!"<<std::endl;
                  return false;
              }
          }
      }
      std::cout<<"Heap!"<<std::endl;
      return true;
}

void MaxHeap::levelorder()
{
	for(int i = 0;i < size;i++)
		std::cout<<data[i]<<" ";
	std::cout<<std::endl;
}
