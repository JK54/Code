#ifndef _QUEUE_H
#define _QUEUE_H

#include "sys_comm.h"
#include "Stack.hpp"
template<typename T>
class Queue;

template<typename T>
class QueueNode
{
	friend class Queue<T>;
	public:
	QueueNode():next(nullptr){}
	QueueNode(const T &x):data(x),next(nullptr){}
	QueueNode(const QueueNode<T> &p){data = p.data;next = p.next;}
	QueueNode(const QueueNode<T> *p){data = p->data;next = p->next;}
	QueueNode<T> *Next(){if(next != nullptr) return next;else return nullptr;}
	bool operator==(const QueueNode<T> *p){return data == p->data;}
	bool operator!=(const QueueNode<T> *p){return data != p->data;}
	bool operator==(const QueueNode<T> &p){return data == p.data;}
	bool operator!=(const QueueNode<T> &p){return data != p.data;}
	T Data(){return data;}
	private:
	T data;
	QueueNode<T> *next;
};

template<typename T>
class Queue
{
	public:
		Queue();
		Queue(T x);
		Queue(const Queue<T> &p);
		~Queue();
		Queue<T>& operator=(const Queue<T> &p){this->Copy(p);return *this;}
		size_t Size(){return size;}
		bool Dequeue(T &p);
		bool Enqueue(const T &x);
		T First(){return first->next->data;}
		void Clear(){T x;while(!IsEmpty())Dequeue(x);}
		void Traverse();
		bool IsEmpty() const {return size == 0;}
		bool Copy(const Queue<T> &p);
		void Reverse();
		bool Equal(Queue<T> &Q);
		//priority queue
		bool Enqueue_Priority(T &x);
		//priority queue for customize class,and it must refine the arithmetic operator < and ==.
		bool Enqueue_Priority_PM(T &x);

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
	first = new QueueNode<T>;
	last = new QueueNode<T>(x);
	first->next = last;
	size = 1;
	assert(first);
}

template<typename T>
Queue<T>::Queue(const Queue<T> &p)
{
	size = 0;
	first = last = new QueueNode<T>;
	this->Copy(p);
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
bool Queue<T>::Enqueue(const T &x)
{
	if(first == nullptr)
	{
		std::cout<<"No Queue"<<std::endl;
		return false;
	}
	else
	{
		last->next = new QueueNode<T>(x);
		last = last->next;
		++size;
		return true;
	}
}

//not the real priority queue.the time complexity is O(n).
template<typename T>
bool Queue<T>::Enqueue_Priority(T &x)
{
	if(first == nullptr)
	{
		std::cout<<"no Queue"<<std::endl;
		return false;
	}
	else
	{
		QueueNode<T> *tmp = new QueueNode<T>(x);
		QueueNode<T> *f = first->next;
		QueueNode<T> *fpre = first;
		while(f != nullptr)
		{
			if(f->data < x)
			{
				fpre = f;
				f = f->next;
			}
			else if(f->data == x)
				return false;
			else
				break;
		}
		if(f == nullptr)
		{
			fpre->next = tmp;
			last = tmp;
		}
		else
		{
			fpre->next = tmp;
			tmp->next = f;
		}
		++size;
		return true;
	}
}

	template<typename T>
bool Queue<T>::Enqueue_Priority_PM(T &x)
{
	if(first == nullptr)
	{
		std::cout<<"no Queue"<<std::endl;
		return false;
	}
	else
	{
		QueueNode<T> *tmp = new QueueNode<T>(x);
		QueueNode<T> *f = first->next;
		QueueNode<T> *fpre = first;
		if(std::string(typeid(x).name(),0,1) == "P")
		{
			while(f != nullptr)
			{
				if(f->data->operator<(x))
				{
					fpre = f;
					f = f->next;
				}
				else if(f->data->operator==(x))
					return false;
				else
					break;
			}
		}
		else
		{
			while(f != nullptr)
			{
				if(f->data < x)
				{
					fpre = f;
					f = f->next;
				}
				else if(f->data == x)
					return false;
				else
					break;
			}

		}
		if(f == nullptr)
		{
			fpre->next = tmp;
			last = tmp;
		}
		else
		{
			fpre->next = tmp;
			tmp->next = f;
		}
		++size;
		return true;
	}
}

template<typename T>
bool Queue<T>::Dequeue(T &p)
{
	if(first->next == nullptr)
		return false;
	p = first->next->data;
	QueueNode<T> *tmp = first->next->next;
	//when the queue have only 1 element,the last pointer must change to first.
	if(first->next == last)
		last = first;
	delete first->next;
	first->next = tmp;
	--size;
	return true;
}

template<typename T>
void Queue<T>::Traverse()
{
	if(first->next == nullptr)
	{
		std::cout<<"Queue is empty.."<<std::endl;
		return;
	}
	for(QueueNode<T> *tmp = first->next;tmp != nullptr; tmp = tmp->next)
		std::cout<<tmp->data<<" ";
	std::cout<<std::endl;
}

template<typename T>
bool Queue<T>::Copy(const Queue<T> &p)
{
	if(p.IsEmpty())
		return false;
	QueueNode<T> *tmp;
	Clear();
	tmp = p.first->next;
	while(tmp != nullptr)
	{
		Enqueue(tmp->data);
		tmp  = tmp->next;
	}
	return true;
}

template<typename T>
void Queue<T>::Reverse()
{
	Stack<T> s;
	T tmp;
	while(!IsEmpty())
	{
		Dequeue(tmp);
		s.Push(tmp);
	}
	while(!s.IsEmpty())
	{
		s.Pop(tmp);
		Enqueue(tmp);
	}
}

template<typename T>
bool Queue<T>::Equal(Queue<T> &Q)
{
	Queue<T> p,q;
	p.Copy(*this);
	q.Copy(Q);
	T p1,q1;
	while(!p.IsEmpty() && !q.IsEmpty())
	{
		p.Dequeue(p1);
		q.Dequeue(q1);
		if(p1 != q1)
			return false;
	}
	if(p.IsEmpty() && q.IsEmpty())
		return true;
	else
		return false;
}
#endif

