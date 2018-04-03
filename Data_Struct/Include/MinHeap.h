#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include "Heap.h"

template<typename T>
class MinHeap : public Heap<T>
{
	public:
		MinHeap() = default;
		MinHeap(const Queue<T> &p);
		virtual ~MinHeap() = default;
		virtual void siftUp() override;
		virtual void siftDown() override;
};

#endif
