#ifndef _QUEUE_H
#define _QUEUE_H

#include "sys_comm.h"

template<typename T>
class QueueNode
{
	public:
		T data;
		QueueNode<T> *next;

		QueueNode():next(nullptr){}
		QueueNode(T x):data(x),next(nullptr){}
		QueueNode(QueueNode<T> &p){data = p.data;next = p.next;}
};

template<typename T>
class Queue
{
	friend bool Enqueue_Priority(Queue<T> &queue,T &x);
	public:
		Queue();
		Queue(T x);
		~Queue();
		
		size_t Size(){return size;}
		bool Dequeue(T &p);
		bool Enqueue(T &x);
		void Traverse();
		bool IsEmpty(){if(first->next == nullptr)return true;else return false;}
		bool Copy(Queue<T> &p);
		
		QueueNode<T> *first;
		QueueNode<T> *last;
		size_t size;
};


#endif
