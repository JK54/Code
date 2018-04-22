#ifndef _QUEUE_H
#define _QUEUE_H

#include "sys_comm.h"

template<typename T>
class Queue;

template<typename T>
class QueueNode
{
	friend class Queue<T>;
	public:
	QueueNode():next(nullptr){}
	QueueNode(T x):data(x),next(nullptr){}
	QueueNode(QueueNode<T> &p){data = p.data;next = p.next;}
	QueueNode<T> *Next(){if(next != nullptr) return next;else return nullptr;}
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
		~Queue();

		size_t Size(){return size;}
		bool Dequeue(T &p);
		bool Enqueue(T &x);
		T First(){return first->next->data;}
		void Clear(){T x;while(!IsEmpty())Dequeue(x);}
		void Traverse();
		bool IsEmpty(){if(first->next == nullptr)return true;else return false;}
		bool Copy(Queue<T> &p);
		bool Enqueue_Priority(T &x);
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
			fpre->next = tmp;
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
			fpre->next = tmp;
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
	if(first->next == last)//when the queue have only 1 element,the last pointer must change to first.
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
bool Queue<T>::Copy(Queue<T> &p)
{
	if(!p.IsEmpty())
	{
		QueueNode<T> *tmp;
		while(first->next != nullptr)
		{
			tmp = first->next;
			first->next = tmp->next;
			delete tmp;
		}
		last = first;
		tmp = p.first->next;
		while(tmp != nullptr)
		{
			last->next = new QueueNode<T>(tmp->data);
			last = last->next;
			tmp  = tmp->next;
		}
		return true;
	}
	else
		return false;
}
#endif

