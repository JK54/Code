#include <iostream>
#include "stack.h"

Stack::~Stack()
{
	while(top != nullptr)
	{
		SNode *p = top;
		top = top->next;
		delete p;
		SNode *p2 = mtop;
		mtop = mtop = mtop->next;
		delete p2;
	}
}

SNode* Stack::push(int x) 
{
	SNode *tmp = new SNode;
	tmp->key = x;
	tmp->next = top;
	top = tmp;
	if(x < min2s)
		min2s = x;
	SNode *tmp2 = new SNode;
	tmp2->key = min2s;
	tmp2->next = mtop;
	mtop = tmp2;
	return top;
}

int Stack::pop()
{
	if(top == nullptr)
	{
		throw "try to pop a empty stack";
	}
	int x = top->key;
	SNode *p = top->next;
	delete top;
	top = p;
	p = mtop->next;
	delete mtop;
	mtop = p;
	return x;
}


int Stack::min()
{
	if(mtop	== nullptr)
		return INT_MAX;
	return mtop->key;
}

int Stack::topelement()
{
	if(top	== nullptr)
		return INT_MAX;
	return top->key;
}

bool Stack::poplist(int a[],int b[],int len)
{

	if(len == 0 && (a == nullptr && b == nullptr))
		return true;
	if(len <= 0 || a == nullptr || b == nullptr)
		return false;
	while(top != nullptr)
		pop();
	int i,j;
	i = 0;j = 0;
	while(j < len)
	{
		if(top != nullptr && topelement() == b[j])
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
			if(i == len && top != nullptr && topelement() != b[j])
				return false;
		}
	}
	return true;
}
