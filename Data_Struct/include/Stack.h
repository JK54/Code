#ifndef _STACK_H
#define _STACK_H

#include "sys_comm.h"

template<typename T>
class StackNode
{
	public:
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
		bool IsEmpty(){if(top == base)return true;else return false;}
		T Max();
		T Min();
	private:
		StackNode<T> *base;
		StackNode<T> *top;
};

#endif
