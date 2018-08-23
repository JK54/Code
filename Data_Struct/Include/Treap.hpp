#ifndef _TREAP_H
#define _TREAP_H

#include "sys_comm.h"

template<typename T>
struct TreapNode
{
	TreapNode(const T &vle)
	{
		std::random_device rd;
		std::mt19937 mr(rd());
		data = vle;
		weight = mr();
		parent = nullptr;
		lchild = nullptr;
		rchild = nullptr;
	}
	T data;
	unsigned int weight;//the synonym for priority.
	TreapNode<T> *parent;
	TreapNode<T> *lchild;
	TreapNode<T> *rchild;
};

template<typename T>
class Treap
{
	public:
		Treap():root(nullptr),count(0){}
		~Treap(){destory(root);}
		void Insert(const T &vle);
		void Remove(const T &vle);
		void Remove_As_Heap(TreapNode<T> *&roo);
		void Remove_As_Tree(TreapNode<T> *&roo);
		void Traverse(TreapNode<T> *roo);
		TreapNode<T>* Search(const T &vle);
		TreapNode<T> *Root(){return root;}
	private:
		void rotatel(TreapNode<T> *&roo);
		void rotater(TreapNode<T> *&roo);
		void change_child(TreapNode<T> *&,TreapNode<T> *&,TreapNode<T> *&);
		void destory(TreapNode<T> *roo);
		
		TreapNode<T> *root;
		size_t count;
};

template<typename T>
void Treap<T>::destory(TreapNode<T> *roo)
{
	if(roo == nullptr)
		return;
	destory(roo->lchild);
	destory(roo->rchild);
	delete roo;
}

template<typename T>
void Treap<T>::Traverse(TreapNode<T> *roo)
{
	if(roo == nullptr)
		return;
	Traverse(roo->lchild);
	std::cout<<roo->data<<" ";
	Traverse(roo->rchild);
}

template<typename T>
inline void Treap<T>::change_child(TreapNode<T> *&roo,TreapNode<T> *&pre,TreapNode<T> *&parent)
{
	if(parent != nullptr)
	{
		if(parent->lchild == pre)
			parent->lchild = roo;
		else
			parent->rchild = roo;
		if(roo != nullptr)
			roo->parent = parent;
	}
	else
	{
		root = roo;
		if(root != nullptr)
			root->parent = nullptr;
	}
}
template<typename T>
inline void Treap<T>::rotatel(TreapNode<T> *&roo)
{
	TreapNode<T> *r = roo->rchild;
	roo->rchild = r->lchild;
	if(roo->rchild != nullptr)
		roo->rchild->parent = roo;
	if(roo->parent != nullptr)
	{
		if(roo->parent->lchild == roo)
			roo->parent->lchild = r;
		else
			roo->parent->rchild = r;
	}
	else
	{
		root = r;
		root->parent = nullptr;
	}
	r->lchild = roo;
	r->parent = roo->parent;
	roo->parent = r;
	roo = r;
}

template<typename T>
inline void Treap<T>::rotater(TreapNode<T> *&roo)
{
	TreapNode<T> *l = roo->lchild;
	roo->lchild = l->rchild;
	if(roo->lchild != nullptr)
		roo->lchild->parent = roo;
	if(roo->parent != nullptr)
	{
		if(roo->parent->lchild == roo)
			roo->parent->lchild = l;
		else
			roo->parent->rchild = l;
	}
	else
	{
		root = l;
		root->parent = nullptr;
	}
	l->rchild = roo;
	l->parent = roo->parent;
	roo->parent = l;
	roo = l;
}

template<typename T>
void Treap<T>::Insert(const T &vle)
{
	TreapNode<T> *trav,*pre;
	pre = nullptr;
	trav = root;
	while(trav != nullptr)
	{
		pre = trav;
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			return;
	}
	trav = new TreapNode<T>(vle);
	trav->parent = pre;
	count++;
	if(pre == nullptr)
	{
		root = trav;
		return;
	}
	else
	{
		if(pre->data > vle)
			pre->lchild = trav;
		else
			pre->rchild = trav;
	}
	while(pre != nullptr && trav->weight < pre->weight)
	{
		if(trav == pre->lchild)
			rotater(pre);
		else
			rotatel(pre);
		trav = pre;
		pre = pre->parent;
	}
}

template<typename T>
TreapNode<T>* Treap<T>::Search(const T &vle)
{
	TreapNode<T> *roo = root;
	while(roo != nullptr)
	{
		if(roo->data == vle)
			return roo;
		else if(roo->data > vle)
			roo = roo->lchild;
		else
			roo = roo->rchild;
	}
	return nullptr;
}
template<typename T>
void Treap<T>::Remove_As_Heap(TreapNode<T> *&roo)
{
	while(roo->lchild != nullptr && roo->rchild != nullptr)
	{
		if(roo->rchild->weight > roo->lchild->weight)
		{
			rotater(roo);
			roo = roo->rchild;
		}
		else
		{
			rotatel(roo);
			roo = roo->lchild;
		}
	}
	if(roo->lchild != nullptr)
		change_child(roo->lchild,roo,roo->parent);
	else
		change_child(roo->rchild,roo,roo->parent);
	delete roo;
	roo = nullptr;
}

template<typename T>
void Treap<T>::Remove_As_Tree(TreapNode<T> *&roo)
{
	TreapNode<T> *trav,*pre;
	trav = roo;
	pre = roo->parent;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	{
		//randomlly get pre or next
		std::random_device rd;
		if(rd() % 2 == 0)
		{
			trav = trav->lchild;
			while(trav->rchild != nullptr)
				trav = trav->rchild;
		}
		else
		{
			trav = trav->rchild;
			while(trav->lchild != nullptr)
				trav = trav->lchild;
		}
		pre->data = trav->data;
		pre = trav;
	}
	if(trav->lchild != nullptr)
		change_child(trav->lchild,trav,pre);
	else
		change_child(trav->rchild,trav,pre);
	delete trav;
	trav = nullptr;
}

template<typename T>
void Treap<T>::Remove(const T &vle)
{
	TreapNode<T> *trav = Search(vle);
	if(trav == nullptr)
		return;
	Remove_As_Tree(trav);
	// Remove_As_Heap(trav);
	count--;
}
#endif
