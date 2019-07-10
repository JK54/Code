#ifndef _MINHEAP_
#define _MINHEAP_
#define N 25
#include "heap.h"

struct MinHeap:public Heap
{
	int *data;
	int size;
	int capacity;
	explicit MinHeap();
	explicit MinHeap(int a[],int n);
	~MinHeap();
	
	void push(int ) override;
	int top() override;
	void pop() override;
	bool isheap() override;
	void levelorder() override;
	void siftup(int start,int end) override;
	void siftdown(int start,int end) override;
	void expantion() override;
	void allocate(int **,int size) override;
};

#endif
