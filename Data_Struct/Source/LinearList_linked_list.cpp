#include "../Include/LinearList_linked_list.h"

template<typename T>
LinkedList<T>::LinkedList()
{
	head = tail = new LNode<T>;
	leng = 0;
	use = new size_t(1);
}

template<typename T>
LinkedList<T>::LinkedList(T x)
{
	head = new LNode<T>;
	tail = new LNode<T>(x);
	head->next = tail;
	leng = 1;
	use = new size_t(1);
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	if(*--use == 0)
	{
		while(head != nullptr)
		{
			LNode<T> *tmp = head->next;
			delete head;
			head = tmp;
		}
	}
}
template<typename T>
bool LinkedList<T>::isempty()
{
	if(head->next == nullptr)
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
			LNode<T> *tmp = head->next;
			LNode<T> *w2i = new LNode<T>(x);
			for(auto j = 1; j < i; ++j)
				tmp = tmp->next;
			w2i->next = tmp->next;
			tmp->next = w2i;
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
bool LinkedList<T>::push_back(T x)
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
		while(tmp->next != tail)tmp = tmp->next;
		x = tail->data;
		delete tail;
		tail = tmp;
		tail->next= nullptr;
		leng--;
		return true;
	}
	else
		return false;
}
