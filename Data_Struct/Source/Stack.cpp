#include "../Include/Stack.h"

template<typename T>
Stack<T>::Stack()
{
	base = top = new StackNode<T>;
	assert(base);
}

template<typename T>
Stack<T>::Stack(T x)
{
	top = base = new StackNode<T>(x);
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