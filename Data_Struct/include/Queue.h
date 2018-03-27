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
	public:
		Queue();
		Queue(T x);
		~Queue();
		
		size_t Size(){return size;}
		bool Dequeue(T &p);
		bool Enqueue(T &x);
		bool IsEmpty(){if(first->next == nullptr)return true;else return false;}
	private:
		QueueNode<T> *first;
		QueueNode<T> *last;
		size_t size;
};


template<typename T>

Queue<T>::Queue()
{
	first = last = new QueueNode<T>;
	size = 0;
	assert(first);
}

template<typename T>
Queue<T>::Queue(T x)
{
	first = new QueueNode<T>(x);
	last = new QueueNode<T>;
	first->next = last;
	size = 1;
	assert(first);
}

template<typename T>
Queue<T>::~Queue()
{
	QueueNode<T> *tmp;
	while(first != nullptr)
	{
		tmp = first->next;
		delete first;
		first = nullptr;
		first = tmp;
	}
	// std::cout<<"Queue destroyed.."<<std::endl;
}

template<typename T>
bool Queue<T>::Enqueue(T &x)
{
	if(first == nullptr)
	{
		std::cout<<"no Queue"<<std::endl;
		return false;
	}
	else
	{
		last->next = new QueueNode<T>(x);
		last = last->next;
		if(first->next == nullptr)
			first->next = last;
		++size;
		return true;
	}
}

template<typename T>
bool Queue<T>::Dequeue(T &p)
{
	if(first->next == nullptr)
	{
		std::cout<<"Queue is empty"<<std::endl;
		return false;
	}
	p = first->next->data;
	QueueNode<T> *tmp = first->next->next;		
	delete first->next;
	first->next = tmp;
	--size;
	return true;
}

#endif
