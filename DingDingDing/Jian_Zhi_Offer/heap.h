#ifndef _HEAP_
#define _HEAP_

struct Heap
{
	Heap(){};
	virtual ~Heap(){};
	virtual void push(int ) = 0;
	virtual int top() = 0 ;
	virtual void pop() = 0;
	virtual bool isheap() = 0;
	virtual void levelorder() = 0;
	virtual void siftup(int start,int end) = 0;
	virtual void siftdown(int start,int end) = 0;
	virtual void expantion() = 0;
	virtual void allocate(int **,int size) = 0;
};

#endif
