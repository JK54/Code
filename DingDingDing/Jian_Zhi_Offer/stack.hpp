#include <iostream>
#include <limits.h>

template<typename T>
struct SNode
{
	T key;
	struct SNode *next;
};


template<typename T>
struct Stack
{
	SNode<T> *topelement,*mtop;
	int sz;
	T min2s;

	Stack():topelement(nullptr),mtop(nullptr),min2s(),sz(0){}
	~Stack();
	void push(T x);
	void pop();
	T min();
	T top();
	int size();
	//给定入站序列a，出栈序列b，判断b是否正确
	bool poplist(int a[],int b[],int len);
};
	
template<typename T>
Stack<T>::~Stack()
{
	while(topelement != nullptr)
	{
		SNode<T> *p = topelement;
		topelement = topelement->next;
		delete p;
		SNode<T> *p2 = mtop;
		mtop = mtop = mtop->next;
		delete p2;
	}
	sz = 0;
}

template<typename T>
int Stack<T>::size()
{
	return sz;
}

template<typename T>
void Stack<T>::push(T x) 
{
	SNode<T> *tmp = new SNode<T>;
	tmp->key = x;
	tmp->next = topelement;
	topelement = tmp;
	if(x < min2s)
		min2s = x;
	SNode<T> *tmp2 = new SNode<T>;
	tmp2->key = min2s;
	tmp2->next = mtop;
	mtop = tmp2;
	sz++;
}

template<typename T>
void Stack<T>::pop()
{
	if(topelement == nullptr)
		return;
	SNode<T> *p = topelement->next;
	delete topelement;
	topelement = p;
	p = mtop->next;
	delete mtop;
	mtop = p;
	sz--;
}


template<typename T>
T Stack<T>::min()
{
	if(mtop	== nullptr)
		return INT_MAX;
	return mtop->key;
}

template<typename T>
T Stack<T>::top()
{
	return topelement->key;
}

template<typename T>
bool Stack<T>::poplist(int a[],int b[],int len)
{

	if(len == 0 && (a == nullptr && b == nullptr))
		return true;
	if(len <= 0 || a == nullptr || b == nullptr)
		return false;
	while(topelement != nullptr)
		pop();
	int i,j;
	i = 0;j = 0;
	while(j < len)
	{
		if(topelement != nullptr && topelement == b[j])
		{
			pop();
			j++;
		}
		else
		{
			while(i < len && a[i] != b[j])
				push(a[i++]);
			if(i < len && a[i] == b[j])
				i++,j++;
			if(i == len && topelement != nullptr && topelement() != b[j])
				return false;
		}
	}
	return true;
}
