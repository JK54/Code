#ifndef _STACK_H
#define _STACK_H

#include "sys_comm.h"

template<typename T>
class Stack;

template<typename T>
class StackNode
{
	friend class Stack<T>;
	T data;
	StackNode<T> *next;
	StackNode():next(nullptr){}
	StackNode(T x):data(x),next(nullptr){}
	StackNode(StackNode<T> &p){data = p.data;next = p.next;}
};

template<typename T>
class Stack
{
	public:
		Stack();
		Stack(T x);
		~Stack();

		bool Pop(T &p);
		bool Push(T &x);
		bool Top(T &p);
		bool IsEmpty(){if(top == base)return true;else return false;}
		size_t Size(){return size;}
		void Traverse();
		T Max();
		T Min();
	private:
		StackNode<T> *base;
		StackNode<T> *top;
		size_t size;
};


template<typename T>
Stack<T>::Stack()
{
	base = top = new StackNode<T>;
	size = 0;
	assert(base);
}

template<typename T>
Stack<T>::Stack(T x)
{
	base = new StackNode<T>;
	top  = new StackNode<T>(x);
	top->next = base;
	size = 1;
	assert(base);
}

template<typename T>
Stack<T>::~Stack()
{
	StackNode<T> *tmp;
	while(top != nullptr)
	{
		tmp = top->next;
		delete top;
		top = nullptr;
		top = tmp;
	}
	// std::cout<<"Stack destroyed.."<<std::endl;
}

template<typename T>
bool Stack<T>::Push(T &x)
{
	if(base == nullptr)
	{
		std::cout<<"no Stack"<<std::endl;
		return false;
	}
	StackNode<T> *tmp = new StackNode<T>(x);
	tmp->next = top;
	top = tmp;
	size++;
	return true;
}

template<typename T>
bool Stack<T>::Pop(T &p)
{
	if(IsEmpty())
		return false;
	p = top->data;
	StackNode<T> *tmp = top->next;
	delete top;
	top = tmp;
	size--;
	return true;
}

template<typename T>
bool Stack<T>::Top(T &p)
{
	if(IsEmpty())
		return false;
	p = top->data;
	StackNode<T> *tmp = top->next;
	return true;
}

template<typename T>
T Stack<T>::Max()
{
	StackNode<T> *tmp = top;
	T max = tmp->data;
	while(tmp != base)
	{
		tmp = tmp->next;
		max = max > tmp->data?max:tmp->data;
	}
	return max;
}

template<typename T>
T Stack<T>::Min()
{
	StackNode<T> *tmp = top;
	T max = tmp->data;
	while(tmp != base)
	{
		tmp = tmp->next;
		max = max < tmp->data?max:tmp->data;
	}
	return max;
}

template<typename T>
void Stack<T>::Traverse()
{
	if(IsEmpty())
		exit(1);
	StackNode<T> *tmp = top;
	while(tmp != base)
	{
		std::cout<<tmp->data<<" ";
		tmp = tmp->next;
	}
	std::cout<<std::endl;
}
#endif
