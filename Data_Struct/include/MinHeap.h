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
template<typename T>
MinHeap<T>::MinHeap(const Queue<T> &p)
{
	Heap<T>::head =  new HeapNode<T>;
	Heap<T>::lastpos = new Queue<HeapNode<T>*>;
	HeapNode<T> *last;
	Queue<HeapNode<T>*> s;
	s.Enqueue(Heap<T>::head);
	QueueNode<T> *sq = p.first->next;
	while(sq != nullptr)
	{
		s.Dequeue(last);
		last->lchild = new HeapNode<T>(sq->data);
		s.Enqueue(last->lchild);
		if(sq->next != nullptr)
		{
			last->rchild = new HeapNode<T>(sq->next->data);
			sq = sq->next;
			s.Enqueue(last->rchild);
		}
		sq = sq->next;
	}
	Heap<T>::lastpos->Copy(s);
	if(last->rchild == nullptr)
//There are only 2 situation of last:1.lchild is occupied,in this situation,push it into the queue;2.both are not nullptr,then ignore last.when both child is nullptr,it's unneccessay to do any job,it already in the queue.
		Heap<T>::lastpos->Enqueue_Priority(last);
}

template<typename T>
void MinHeap<T>::siftUp()
{
	  
}

template<typename T>
void MinHeap<T>::siftDown()
{
	
}
#endif
