#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include "Heap_LinkedBST.hpp"

template<typename T>
class MinHeap : public Heap<T>
{
	public:
		MinHeap() = default;
		MinHeap(Queue<T> &p);
		virtual ~MinHeap() = default;
		virtual void siftUp() override{}
		virtual void siftDown() override{}
	private:
		void Swap(HeapNode<T> &p);
};


template<typename T>
MinHeap<T>::MinHeap(Queue<T> &p)
{
	Heap<T>::head =  new HeapNode<T>;
	Heap<T>::lastpos = new Queue<HeapNode<T>*>;
	HeapNode<T> *last = nullptr;
	Queue<HeapNode<T>*> s;
	s.Enqueue(Heap<T>::head);
	QueueNode<T> *sq = p.First();
	while(sq != nullptr)
	{
		s.Dequeue(last);
		last->lchild = new HeapNode<T>(sq->Data());
		s.Enqueue(last->lchild);
		if(sq->Next() != nullptr)
		{
			last->rchild = new HeapNode<T>(sq->Next()->Data());
			sq = sq->Next();
			s.Enqueue(last->rchild);
		}
		sq = sq->Next();
	}
	Heap<T>::lastpos->Copy(s);
	if(last->rchild == nullptr)
//There are only 2 situation of last:1.lchild is occupied,in this situation,push it into the queue;2.both are not nullptr,then ignore last.when both child is nullptr,it's unneccessay to do any job,it already in the queue.
	Heap<T>::lastpos->Enqueue_Priority_PM(last);
}

#endif
