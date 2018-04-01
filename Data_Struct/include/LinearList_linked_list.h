#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include "sys_comm.h"

template<typename T>
class LinkedList;

template<typename T>
class LNode
{
	public:
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
		bool push_back(T x);
		bool push_forward(T x);
		bool pop_back(T &x);
		bool pop_forward(T &x);
		
		LNode<T>* head;
		LNode<T>* tail;
		size_t leng;
		size_t *use;
};

#endif
