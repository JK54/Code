#ifndef _FIBONACCI_HEAP_H
#define _FIBONACCI_HEAP_H

#include "sys_comm.h"

//definition of fibonacci heap:the max degree of the heap fits the fibonacci series.

template<typename T>
struct FibNode
{
	FibNode(){}
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
	protected:
		void swap(FibNode<T> *&x,FibNode<T> *&y){FibNode<T> *tmp;tmp = x;x = y;y = tmp;}
		T max(const T &v1,const T &v2){return v1 > v2 ? v1 : v2;}
		T min(const T &v1,const T &v2){return v1 < v2 ? v1 : v2;}
		void link(FibNode<T> *&x,FibNode<T> *&y);
		void pickup(FibNode<T> *&result,FibNode<T> *&root);
		void destroy(FibNode<T> *);
		void consolidate(FibNode<T> *&root,size_t count,bool is_minheap);
		void insert(const T &vle,FibNode<T> *&root,bool is_minheap);
		void insert(FibNode<T> *trav,FibNode<T> *&root,bool is_minheap);
		void unionheap(FibNode<T> *&h1,FibNode<T> *&h2,bool is_minheap);
		void change_key(FibNode<T> *&,FibNode<T> *&,const T &vle,bool is_minheap);//increase or decrease.
		void cut(FibNode<T> *&child,FibNode<T> *&parent,FibNode<T> *&root,bool is_minheap);
		void cascadingcut(FibNode<T> *&p,FibNode<T> *&root,bool is_minheap);
		void del(FibNode<T> *&roo,FibNode<T> *&root,const T &boundary,bool is_minheap);
};

template<typename T>
class MinFibHeap : public FibHeap<T>
{
	public:
		MinFibHeap():min(nullptr),count(0){}
		MinFibHeap(const T &vle):min(new FibNode<T>(vle)),count(1){}
		~MinFibHeap(){this->destroy(min);}
		void Insert(const T &vle);
		void Union(MinFibHeap<T> &f2);
		FibNode<T>* Minimum(){return min;}
		FibNode<T>* Extract_Min();
		void Decrease_Key(FibNode<T> *,const T &vle);
		void Delete(FibNode<T> *,const T &boundary);
		FibNode<T> *Min(){return min;}
	private:
		FibNode<T> *min;
		size_t count;

};

template<typename T>
class MaxFibHeap : public FibHeap<T>
{
	public:
		MaxFibHeap():max(nullptr),count(0){}
		MaxFibHeap(const T &vle):max(new FibNode<T>(vle)),count(1){}
		~MaxFibHeap(){this->destroy(max);}
		void Insert(const T &vle);
		void Union(MaxFibHeap<T> &f2);
		FibNode<T>* Maximum(){return max;}
		FibNode<T>* Extract_Max();
		void Decrease_Key(FibNode<T> *,const T &vle);
		void Delete(FibNode<T> *,const T &boundary);
		FibNode<T> *Max(){return max;}

	private:
		FibNode<T> *max;
		size_t count;

};


//------------------------FibHeap------------------------------//
template<typename T>
void FibHeap<T>::destroy(FibNode<T> *roo)
{
	FibNode<T> *stone;
	if(roo != nullptr)
		roo->left->right = nullptr;
	while(roo != nullptr)
	{
		if(roo->child != nullptr)
			destroy(roo->child);
		stone = roo->right;
		delete roo;
		roo = stone;
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
			root->left->right = child;
			root->left = child->left;
			child->left->right = root;
			child->left = root->left;
		}
		if(root->right != root)
		{
			root->right->left = root->left;
			root->left->right = root->right;
			root = root->right;
		}
		else
			root = nullptr;
	}
}

//assume that the list has two node at least.
template<typename T>
void FibHeap<T>::link(FibNode<T> *&x,FibNode<T> *&y)
{
	if(x->child != nullptr)
	{
		y->left = x->child->left;
		y->right = x->child;
		x->child->left->right = y;
		x->child->left = y;
	}
	else
	{
		x->child = y;
		y->right = y;
		y->left = y;
	}
	x->degree++;
	y->parent = x;
	y->marked = false;
}

template<typename T>
void FibHeap<T>::consolidate(FibNode<T> *&root,size_t count,bool is_minheap)
{
	int i,maxdegree;
	FibNode<T> **A,*x,*y;
	maxdegree = log(count) / log(1.618) + 1;
	A = new FibNode<T>* [maxdegree];
	for(i = 0;i < maxdegree;i++)
		A[i] = nullptr;
	//endstone.
	root->left->right = nullptr;
	x = root;
	while(x != nullptr)
	{
		while(A[x->degree] != nullptr)
		{
			y = A[x->degree];
			if(is_minheap)
			{
				if(x->key > y->key)
					swap(x,y);
			}
			else
			{
				if(x->key < y->key)
					swap(x,y);
			}
			A[x->degree] = nullptr;
			link(x,y);
		}
		A[x->degree] = x;
		x = x->right;
	}
	root = nullptr;
	for(i = 0;i < maxdegree;i++)
	{
		if(A[i] != nullptr)
			insert(A[i],root,is_minheap);
	}
}

template<typename T>
void FibHeap<T>::insert(const T &vle,FibNode<T> *&root,bool is_minheap) 
{
	FibNode<T> *tmp = new FibNode<T>(vle);
	if(root == nullptr)
		root = tmp;
	else
	{
		tmp->right = root->right;
		root->right->left = tmp;
		root->right = tmp;
		tmp->left = root;
		if((vle < root->key && is_minheap) || (vle > root->key && !is_minheap))
			root = tmp;
	}
}
template<typename T>
void FibHeap<T>::insert(FibNode<T> *trav,FibNode<T> *&root,bool is_minheap) 
{
	if(root == nullptr)
	{
		root = trav;
		root->left = root;
		root->right = root;
	}
	else
	{
		root->right->left = trav;
		trav->right = root->right;
		root->right = trav;
		trav->left = root;
		if((trav->key < root->key && is_minheap) || (trav->key > root->key && !is_minheap))
			root = trav;
	}
}
template<typename T>
void FibHeap<T>::unionheap(FibNode<T> *&root1,FibNode<T> *&root2,bool is_minheap)
{
	if(root1 != nullptr && root2 != nullptr)
	{
		root1->right->left = root2->left;
		root2->left->right = root1->right;
		root1->right = root2;
		root2->left = root1;
		
	}
	if(root1 == nullptr || (root2 != nullptr && ((root2->key < root1->key && is_minheap) || (root2->key > root1->key && ! is_minheap))))
		root1 = root2;
}

template<typename T>
void FibHeap<T>::change_key(FibNode<T> *&roo,FibNode<T> *&root,const T &vle,bool is_minheap)
{
	if((is_minheap && roo->key < vle) || (!is_minheap && roo->key > vle))
		return;
	roo->key = vle;
	FibNode<T> *parent = roo->parent;
	if(parent != nullptr && ((roo->key < parent->key && is_minheap) || (roo->key > parent->key && !is_minheap)))
	{
		cut(roo,parent,root,is_minheap);
		cascadingcut(parent,root,is_minheap);
	}
	if((roo->key < root->key && is_minheap) || (roo->key > root->key && !is_minheap))
		root = roo;
}

template<typename T>
void FibHeap<T>::cut(FibNode<T> *&child,FibNode<T> *&parent,FibNode<T> *&root,bool is_minheap)
{
	child->parent = nullptr;
	child->marked = false;
	if(child->right == child)
	{
		parent->child = nullptr;
	}
	else
	{
		parent->child = child->right;
		child->right->left = child->left;
		child->left->right = child->right;
	}
	unionheap(root,child,is_minheap);
}

template<typename T>
void FibHeap<T>::cascadingcut(FibNode<T> *&p,FibNode<T> *&root,bool is_minheap)
{
	FibNode<T> *pp = p->parent;
	if(pp != nullptr)
	{
		if(p->marked == false)
			p->marked = true;
		else
		{
			cut(p,pp,root,is_minheap);
			cascadingcut(pp,root,is_minheap);
		}
	}
}

template<typename T>
void FibHeap<T>::del(FibNode<T> *&wanted,FibNode<T> *&root,const T &boundary,bool is_minheap)
{
	FibNode<T> *tmp;
	//boundary is the value which is most biggest in maxheap and smallest in minheap.
	change_key(wanted,root,boundary,is_minheap);
	pickup(tmp,root);
}
//------------------------FibHeap End--------------------------------//
//------------------------MinFibHeap Begin---------------------------//


template<typename T>
void MinFibHeap<T>::Insert(const T &vle)
{
	this->insert(vle,min,true);
	count++;
}

template<typename T>
void MinFibHeap<T>::Union(MinFibHeap<T> &f2)
{
	this->unionheap(min,f2.min,true);
	count += f2.count;
	f2.count = 0;
	f2.min = nullptr;
}

template<typename T>
FibNode<T>* MinFibHeap<T>::Extract_Min()
{
	FibNode<T> *result;
	this->pickup(result,min);
	if(result != nullptr)
	{
		count--;
		this->consolidate(min,count,true);
	}
	return result;
}

template<typename T>
void MinFibHeap<T>::Decrease_Key(FibNode<T> *roo,const T &vle)
{
	this->change_key(roo,min,vle,true);
}
template<typename T>
void MinFibHeap<T>::Delete(FibNode<T> *roo,const T &boundary)
{
	this->del(roo,min,boundary,true);
}
//-----------------------MinFibHeap End------------------------------//
	
template<typename T>
void MaxFibHeap<T>::Insert(const T &vle)
{
	this->insert(vle,max,false);
	count++;
}

template<typename T>
void MaxFibHeap<T>::Union(MaxFibHeap<T> &f2)
{
	this->unionheap(max,f2.max,false);
	count += f2.count;
	f2.count = 0;
	f2.max = nullptr;
}

template<typename T>
FibNode<T>* MaxFibHeap<T>::Extract_Max()
{
	FibNode<T> *result;
	this->pickup(result,max);
	if(result != nullptr)
	{
		count--;
		this->consolidate(max,count,false);
	}
	return result;
}

template<typename T>
void MaxFibHeap<T>::Decrease_Key(FibNode<T> *roo,const T &vle)
{
	this->change_key(roo,max,vle,false);
}

template<typename T>
void MaxFibHeap<T>::Delete(FibNode<T> *roo,const T &boundary)
{
	this->del(roo,max,boundary,false);
}

#endif
