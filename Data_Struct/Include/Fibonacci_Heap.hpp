#ifndef _FIBONACCI_HEAP_H
#define _FIBONACCI_HEAP_H

#include "sys_comm.h"

template<typename T>
struct FibNode
{
	FibNode(T vle):key(vle),degree(0),marked(false),parent(nullptr),child(nullptr),left(this),right(this){}
	T key;
	size_t degree;
	bool marked;
	FibNode *parent;
	FibNode *child;
	FibNode *left;
	FibNode *right;
};

template<typename T>
class FibHeap
{
	public:
	protected:
		T max(const T &v1,const T &v2){return v1 > v2 ? v1 : v2;}
		void link(FibNode<T> *x,FibNode<T> *y);
		void pickup(FibNode<T> *&result,FibNode<T> *&root);
		void destroy(FibNode<T> *);
		void consolidate(FibNode<T> *&root,bool is_minheap);
		void insert(const T &vle,FibNode<T> *&root);
		void unionheap(FibNode<T> *&h1,FibNode<T> *&h2,bool is_minheap);
};

template<typename T>
class MinFibHeap : public FibHeap<T>
{
	public:
		MinFibHeap():min(nullptr),count(0){}
		~MinFibHeap(){this->destroy(min);}
		void Insert(const T &vle);
		void Union(MinFibHeap<T> &f2);
		FibNode<T>* Minimum(){return min;}
		FibNode<T>* Extract_Min();
		bool Decrease_Key(FibNode<T> *,const T &vle);

	private:
		FibNode<T> *min;
		size_t count;

};

template<typename T>
class MaxFibHeap : public FibHeap<T>
{
	public:
	private:
		FibNode<T> *max;
		size_t count;
		size_t maxdegree;
};


//------------------------FibHeap------------------------------//
template<typename T>
void FibHeap<T>::destroy(FibNode<T> *roo)
{
	while(roo != nullptr)
	{
		roo->left->right = nullptr;
		if(roo->child != nullptr)
			destroy(roo->child);
		roo = roo->right;
		delete roo->left;
	}
}

template<typename T>
void FibHeap<T>::pickup(FibNode<T> *&result,FibNode<T> *&root)
{
	result = root;
	FibNode<T> *child;
	if(result != nullptr)
	{
		child = root->child;
		//set endstone
		if(child != nullptr)
		{
			child->left->right = nullptr;
			//set parent of children as nullptr
			while(child != nullptr)
			{
				child->parent = nullptr;
				child = child->right;
			}
			//change the pointer of boundary child node.
			child = root->child;
			root->right->left = child->left;
			root->right = child;
			child->left->right = root->right;
			child->left = root;
		}
		if(root->right != root)
			root = root->right;
		else
			root = nullptr;
	}
}

//assume that the list has two node at least.
template<typename T>
void FibHeap<T>::link(FibNode<T> *x,FibNode<T> *y)
{
	y->right->left = y->left;
	y->left->right = y->right;
	if(x->child != nullptr)
	{
		x->child->left = y;
		x->child->left->right = y;
		y->right = x->child;
		y->left = x->child->left;
	}
	x->child = y;
	y->parent = x;
	x->degree++;
}

template<typename T>
void FibHeap<T>::consolidate(FibNode<T> *&root,bool is_minheap)
{

}

template<typename T>
void FibHeap<T>::insert(const T &vle,FibNode<T> *&root) 
{
	FibNode<T> *tmp = new FibNode<T>(vle);
	if(root == nullptr)
		root = tmp;
	else
	{
		if(vle < root->key)
			root = tmp;
		else
		{
			tmp->right = root->right;
			root->right->left = tmp;
			root->right = tmp;
			tmp->left = root;
		}
	}
}

template<typename T>
void FibHeap<T>::unionheap(FibNode<T> *&h1,FibNode<T> *&h2,bool is_minheap)
{
	FibNode<T> *tmp,*f1ml,*f2ml;
	if(h1 != nullptr)
		f1ml = h1->left;
	if(h2 != nullptr)
		f2ml = h2->left;
	if(f1ml != nullptr && f2ml != nullptr)
	{
		f1ml->right = h2;
		h2->left = f1ml;
		h1->left = f2ml;
		f2ml->right = h1;
	}
	if(h1 == nullptr || (h2 != nullptr && (h2->key < h1->key && is_minheap)))
			h1 = h2;
	h2 = nullptr;//f2 no longer used.
}
//------------------------FibHeap End--------------------------------//
//------------------------MinFibHeap Begin---------------------------//


template<typename T>
void MinFibHeap<T>::Insert(const T &vle)
{
	this->insert(vle,min);
	count++;
}

template<typename T>
void MinFibHeap<T>::Union(MinFibHeap<T> &f2)
{
	this->unionheap(min,f2.min,true);
	count += f2.count;
	f2.count = 0;
}

template<typename T>
FibNode<T>* MinFibHeap<T>::Extract_Min()
{

	FibNode<T> *result;
	this->pickup(result,min);
	if(result != nullptr)
	{
		count--;
		this->consolidate(min,true);
	}
	return result;
}

//-----------------------MinFibHeap End------------------------------//
#endif
