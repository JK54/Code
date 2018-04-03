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
	bool operator<(const HeapNode<T> *p){std::cout<<"less2"<<std::endl;return data < p->data;}
	bool operator==(const HeapNode<T> *p){std::cout<<"equal1"<<std::endl;return data == p->data;}
	bool operator==(const HeapNode<T> &p){std::cout<<"equal2"<<std::endl;return data == p.data;}
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

#endif
