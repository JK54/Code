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
		LNode():next(nullptr){}
		LNode(T x):data(x),next(nullptr){}
		bool operator<(const LNode<T> &p){return data < p.data;}
		bool operator<(const LNode<T> *p){return data < p->data;}
		bool operator>(const LNode<T> &p){return data > p.data;}
		bool operator>(const LNode<T> *p){return data > p->data;}
		bool operator==(const LNode<T> &p){return data == p.data;}
		bool operator==(const LNode<T> *p){return data == p->data;}
		bool operator<=(const LNode<T> &p){return data <= p.data;}
		bool operator<=(const LNode<T> *p){return data <= p->data;}
		bool operator>=(const LNode<T> &p){return data >= p.data;}
		bool operator>=(const LNode<T> *p){return data >= p->data;}
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
		LNode<T>* Head(){return head->next;}
		LNode<T>* Tail(){return tail;}
		size_t Length();
		void Traverse();
		bool isempty();
		LNode<T> *Next(LNode<T> *p){return p->next;}
		bool Insert(size_t i,T x);
		bool push_back(const T &x);
		bool push_forward(const T &x);
		bool push_forward(LNode<T> *p);
		bool pop_back(T &x);
		bool pop_forward(T &x);
		bool Delete(T roo,T &re);
		void ReverseMerge(LinkedList<T> &);
		void ReversePart(LNode<T> *pr,LNode<T> *p,const int &n);
		void Reverse();
		void RemoveRange(const T &min,const T &max);
		void RemoveRange_U(const T &min,const T &max);
		void DepartOD(LinkedList<T> &odd,LinkedList<T> &even);
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
	if(head->next == nullptr)
	{
		// std::cout<<"empty list"	<<std::endl;
		return true;
	}
	else
		return false;
}

	template<typename T>
size_t LinkedList<T>::Length()
{
	return leng;
}

	template<typename T>
void LinkedList<T>::Traverse()
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
			std::cout<<"i is bigger than the Length"<<std::endl;
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
		tail->next = t;
		tail = t;
		leng++;
		return true;
	}
	else
		return false;
}

	template<typename T>
bool LinkedList<T>::push_forward(const T &x)
{
	if(head != nullptr)
	{
		LNode<T> *t = new LNode<T>(x);
		t->next = head->next;
		head->next = t;
		leng++;
		return true;
	}
	else
		return false;
}

	template<typename T>
bool LinkedList<T>::push_forward(LNode<T> *p)
{
	if(head != nullptr)
	{
		p->next = head->next;
		head->next = p;
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
		leng--;
		if(leng == 0)
			tail = head;
		delete tmp;
		return true;
	}
	else
		return false;
}

	template<typename T>
bool LinkedList<T>::Delete(T roo,T &re)
{
	if(isempty())
		return false;
	LNode<T> *p,*pre;
	p = head;
	pre = nullptr;
	while(p != nullptr && p->data != roo)
		pre = p,p = p->next;
	if(p == nullptr)
		return false;
	//if p is the tail,the tail pointer must be changed.and the head node does not store data,and just keep it.
	if(p == tail)
		tail = pre;
	pre->next = p->next;
	re = p->data;
	delete p;
	p = nullptr;
	leng--;
	return true;
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
		if(leng == 0)
			tail = head;
		return true;
	}
	else
		return false;
}

	template<typename T>
void LinkedList<T>::ReverseMerge(LinkedList<T> &L)
{
	LNode<T> *pa,*pb,*q;
	pa = head->next;
	pb = L.head->next;
	head->next = nullptr;
	delete L.head;
	L.head = nullptr;
	while (pa != nullptr && pb != nullptr)
	{
		if(pa->operator<=(pb))
		{
			q = pa;
			pa = pa->next;
		}
		else
		{
			q = pb;
			pb = pb->next;;
		}
		q->next = head->next;
		head->next = q;
	}
	if(pb != nullptr)
		pa = pb;
	while(pa != nullptr)
	{
		q = pa;
		pa = pa->next;
		q->next = head->next;
		head->next = q;
	}
	while(q->next != nullptr)
		q = q->next;
	tail = q;
}

	template<typename T>
void LinkedList<T>::ReversePart(LNode<T> *pr,LNode<T> *p,const int &n)
{
	LNode<T> *ppr = pr;
	LNode<T> *q;
	int count = 0;
	while(p != nullptr && count < n)
	{
		q = p->next;
		p->next = pr;
		pr = p;
		p = q;
		count++;
	}
	if(p == nullptr)
	{
		q = head->next;
		q->next = nullptr;
		tail = q;
		head->next = pr;
	}
	else
	{
		tail->next = pr;
		ppr->next = p;
		while(p->next != ppr)
			p = p->next;
		p->next = nullptr;
		tail = p;
	}
}

	template<typename T>
void LinkedList<T>::Reverse()
{
	LNode<T> *pr = head->next;
	LNode<T> *p = pr->next;
	LNode<T> *q;
	while(p != nullptr)
	{
		q = p->next;
		p->next = pr;
		pr = p;
		p = q;
	}
	q = head->next;
	q->next = nullptr;
	head->next = tail;
	tail = q;
}

	template<typename T>
void LinkedList<T>::RemoveRange(const T &min,const T &max)
{
	LNode<T> *pr,*p;
	pr = head;
	p = head->next;
	while(p != nullptr && p->data < min)
	{
		pr = p;
		p = p->next;
	}
	//we can delete element during the serach process,unnecessay to do it after locate the finished position.
	while(p != nullptr && p->data <= max)
	{
		pr->next = p->next;
		delete p;
		p = pr->next;
	}
}

	template<typename T>
void LinkedList<T>::RemoveRange_U(const T &min,const T &max)
{
	LNode<T> *pr,*p;
	pr = head;
	p = head->next;
	while(p != nullptr)
	{
		if(p->data >= min && p->data <= max)
		{
			pr->next = p->next;
			delete p;
			p = pr->next;
		}
		else
		{
			pr = p;
			p = p->next;
		}
	}
}

	template<typename T>
void LinkedList<T>::DepartOD(LinkedList<T> &odd,LinkedList<T> &even)
{
	LNode<T> *p = head->next;
	while(p != nullptr)
	{
		if(p->data %2 == 0)
			even.push_back(p->data);
		else
			odd.push_back(p->data);
		p = p->next;
	}
}
#endif
