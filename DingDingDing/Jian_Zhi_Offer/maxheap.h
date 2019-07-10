#ifndef _MAXHEAP_
#define _MAXHEAP_
#define N 25
#include "heap.h"

struct MaxHeap:public Heap
{
	int *data;
	int size;
	int capacity;
	explicit MaxHeap();
	explicit MaxHeap(int a[],int n);
	~MaxHeap();
	
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
