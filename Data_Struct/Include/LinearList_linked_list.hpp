#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include "sys_comm.h"

template<typename T>
class LinkedList;

template<typename T>
class LNode
{
	friend class LinkedList<T>;
	LNode():data(0),next(nullptr){}
	LNode(T x):data(x),next(nullptr){}
	T data;
	LNode<T> *next;
};

template<typename T>
class LinkedList
{
	public:
		LinkedList();
		LinkedList(T x);
		~LinkedList();
		LinkedList(const LinkedList<T> &p);
		LinkedList<T>& operator=(const LinkedList<T> &p);
		T* Head(){return head;}
		T* Tail(){return tail;}
		size_t length();
		void traverse();
		bool isempty();
		bool Insert(size_t i,T x);
		bool push_back(const T &x);
		bool push_forward(T x);
		bool pop_back(T &x);
		bool pop_forward(T &x);
		void qsort();
		void ReverseMerge(LinkedList<T> &);
	private:		
		LNode<T>* head;
		LNode<T>* tail;
		size_t leng;
};

template<typename T>
LinkedList<T>::LinkedList()
{
	head = tail = new LNode<T>;
	leng = 0;
}

template<typename T>
LinkedList<T>::LinkedList(T x)
{
	head = new LNode<T>;
	tail = new LNode<T>(x);
	head->next = tail;
	leng = 1;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	while(head != nullptr)
	{
		LNode<T> *tmp = head->next;
		delete head;
		head = tmp;
	}
}
template<typename T>
bool LinkedList<T>::isempty()
{
	if(head == nullptr)
	{
		std::cout<<"empty list"	<<std::endl;
		return true;
	}
	else
		return false;
}

template<typename T>
size_t LinkedList<T>::length()
{
	std::cout<<"length is "<<leng<<std::endl;
	return leng;
}

template<typename T>
void LinkedList<T>::traverse()
{
	if(!isempty())
	{
		for(auto p = head->next; p != nullptr; p = p->next)
			std::cout<<p->data<<" ";
		std::cout<<std::endl;
	}
	else
		return;
}

template<typename T>
bool LinkedList<T>::Insert(size_t i, T x)
{
	if(!isempty())
	{
		if(i <= leng)
		{
			LNode<T> *tmp = head;
			LNode<T> *w2i = new LNode<T>(x);
			for(auto j = 0; j <= i; ++j)
				tmp = tmp->next;
			w2i->next = tmp->next;
			tmp->next = w2i;
			if(i == leng)
				tail = w2i;
			++leng;
			return true;
		}
		else
		{
			std::cout<<"i is bigger than the length"<<std::endl;
			return false;
		}
	}
	else
		return false;
}

template<typename T>
bool LinkedList<T>::push_back(const T &x)
{
	if(head != nullptr)
	{
		LNode<T> *t = new LNode<T>(x);
		t->data = x;//tail->next == t->next == nullptr,不需要重新复制尾指针
		tail->next = t;
		tail = t;
		leng++;
		return true;
	}
	else
		return false;
}

template<typename T>
bool LinkedList<T>::push_forward(T x)
{
	if(!isempty())
	{
		LNode<T> *t = new LNode<T>(x);
		t->data = x;
		t->next = head->next;
		head->next = t;
		leng++;
		return true;
	}
	else
		return false;
}

template<typename T>
bool LinkedList<T>::pop_forward(T &x)
{
	if(!isempty())
	{
		x = head->next->data;
		LNode<T> *tmp = head->next;
		head->next = head->next->next;
		delete tmp;
		tmp = nullptr;
		leng--;
		return true;
	}
	else
		return false;
}

template<typename T>
bool LinkedList<T>::pop_back(T &x)
{
	if(!isempty())
	{
		x = tail->data;
		LNode<T> *tmp = head;
		while(tmp->next != tail)
			tmp = tmp->next;
		delete tail;
		tail = tmp;
		tail->next= nullptr;
		leng--;
		return true;
	}
	else
		return false;
}

template<typename T>
void qsort()
{}
#endif
