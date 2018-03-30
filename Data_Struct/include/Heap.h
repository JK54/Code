#ifndef _HEAP_H
#define _HEAP_H

#include "Queue.h"
#include "Stack.h"
#include "sys_comm.h"


//It's better to use array,because heap is a complete binary tree.
template<typename T>
struct HeapNode
{
	T data;
	HeapNode<T> *lchild;
	HeapNode<T> *rchild;
	HeapNode(T x = 0):data(x),lchild(nullptr),rchild(nullptr){}
	bool operator<(const HeapNode<T> &p){std::cout<<"less1"<<std::endl;return data < p.data;}
	bool operator<(const HeapNode<T> *p){std::cout<<"less"<<std::endl;return data < p->data;}
	bool operator==(const HeapNode<T> *p){std::cout<<"equal"<<std::endl;return data == p->data;}
	bool operator!=(const HeapNode<T> *p){std::cout<<"not equal"<<std::endl;return data != p->data;}
	void Swap(HeapNode<T> *p){T tmp = p->data;p->data = data;data = tmp;}
};

template<typename T>
class Heap
{
	public:
		Heap();
		Heap(const Queue<T> &p);
		virtual ~Heap();

		bool IsEmpty();
		void Insert(T &x);
		bool Remove(T &x);//x as the the parameter to accept top of heap and delete top.
		void TraversePostOrder();
		void TraverseLevelOrder();
		virtual void siftDown() = 0;
		virtual void siftUp() = 0;
	protected:
		HeapNode<T> *head;
		Queue<HeapNode<T>*> *lastpos;
};

template<typename T>
Heap<T>::Heap()
{
	head = new HeapNode<T>;
	lastpos = new Queue<HeapNode<T>*>;
	lastpos->first = lastpos->last = new QueueNode<HeapNode<T> *>;
}

template<typename T>
Heap<T>::Heap(const Queue<T> &p)//the queue is actually builded as priority queue.
{
	head =  new HeapNode<T>;
	lastpos = new Queue<HeapNode<T>*>;
	HeapNode<T> *last;
	Queue<HeapNode<T>*> s;
	s.Enqueue(head);
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
	lastpos->Copy(s);
	if(last->rchild == nullptr)
//There are only 2 situation of last:1.lchild is occupied,in this situation,push it into the queue;2.both are not nullptr,then ignore last.when both child is nullptr,it's unneccessay to do any job,it already in the queue.
		lastpos->Enqueue_Priority(last);
}

template<typename T>
Heap<T>::~Heap()
{
	HeapNode<T> *p = head;
	Queue<HeapNode<T>*> s;
	s.Enqueue(p);
	while(s.Dequeue(p))
	{
		if(p->lchild != nullptr)
			s.Enqueue(p->lchild);
		if(p->rchild != nullptr)
			s.Enqueue(p->rchild);
		delete p;
		p = nullptr;
	}
	lastpos->~Queue();
}

template<typename T>
bool Heap<T>::IsEmpty()
{
	if(head == nullptr)
		return true;
	else
		return false;
}

template<typename T>
void Heap<T>::TraversePostOrder()
{
	Stack<HeapNode<T>*> s;
	HeapNode<T> *p = head;
	HeapNode<T> *pre = nullptr;
	while(p != nullptr)
	{
		s.Push(p);
		p = p->lchild;
	}
	while(!s.IsEmpty())
	{
		s.Pop(p);
		if(p->rchild == nullptr || p->rchild == pre)	
		{
			std::cout<<p->data<<" ";
			pre = p;
		}
		else
		{
			s.Push(p);
			p = p->rchild;
			while(p != nullptr)
			{
				s.Push(p);
				p = p->lchild;
			}
		}
	}
	std::cout<<std::endl;
}

template<typename T>
void Heap<T>::TraverseLevelOrder()
{
	HeapNode<T> *p = head;
	Queue<HeapNode<T>*> s;
	s.Enqueue(p);
	while(!s.IsEmpty())
	{
		s.Dequeue(p);
		std::cout<<p->data<<" ";
		if(p->lchild != nullptr)
		s.Enqueue(p->lchild);
		if(p->rchild != nullptr)
		s.Enqueue(p->rchild);
	}
	std::cout<<std::endl;
}

template<typename T>
void Heap<T>::Insert(T &x)
{
	HeapNode<T> *tmp;
	lastpos->Dequeue(tmp);
	if(tmp->lchild == nullptr)
	{
		tmp->lchild = new HeapNode<T>(x);
		lastpos->Enqueue_Priority(tmp);
		lastpos->Enqueue(tmp->lchild);
	}
	else
	{
		tmp->rchild = new HeapNode<T>(x);
		lastpos->Enqueue(tmp->rchild);
	}
}
#endif
