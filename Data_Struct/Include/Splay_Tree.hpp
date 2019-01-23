#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

#include "sys_comm.h"

template<typename T>
struct SpTreeNode
{
	SpTreeNode(T vle):data(vle),parent(nullptr),lchild(nullptr),rchild(nullptr){}
	T data;
	SpTreeNode<T> *parent;
	SpTreeNode<T> *lchild;
	SpTreeNode<T> *rchild;
};

template<typename T>
class SpTree
{
	public:
		SpTree():root(nullptr),count(0){}
		~SpTree(){destroy(root);}
		void Insert(const T &vle);
		void Remove(const T &vle);
		void TraversePreorder(SpTreeNode<T> *roo);
		void TraverseInorder(SpTreeNode<T> *roo);
		SpTreeNode<T>* Search(const T &vle);
		SpTreeNode<T>* Root(){return root;}
	private:
		void destroy(SpTreeNode<T> *roo);
		SpTreeNode<T>* first();
		SpTreeNode<T>* last();
		void replace_child(SpTreeNode<T> *&,SpTreeNode<T> *&,SpTreeNode<T> *&);
		void rotatel(SpTreeNode<T> *&roo);
		void rotater(SpTreeNode<T> *&roo);
		SpTreeNode<T> *root;
		size_t count;
};

template<typename T>
void SpTree<T>::destroy(SpTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	destroy(roo->lchild);
	destroy(roo->rchild);
	delete roo;
}

template<typename T>
void SpTree<T>::TraversePreorder(SpTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	std::cout<<roo->data<<" ";
	TraversePreorder(roo->lchild);
	TraversePreorder(roo->rchild);
}
template<typename T>
void SpTree<T>::TraverseInorder(SpTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	TraverseInorder(roo->lchild);
	std::cout<<roo->data<<" ";
	TraverseInorder(roo->rchild);
}
template<typename T>
void SpTree<T>::Insert(const T &vle)
{
	SpTreeNode<T> *pre,*trav;
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
	trav = new SpTreeNode<T>(vle);
	trav->parent = pre;
	count++;
	if(pre == nullptr)
	{
		root = trav;
		return;
	}
	if(pre->data > vle)
		pre->lchild = trav;
	else
		pre->rchild = trav;
}

template<typename T>
inline void SpTree<T>::replace_child(SpTreeNode<T> *&newone,SpTreeNode<T> *&oldone,SpTreeNode<T> *&parent)
{
	if(parent != nullptr)
	{
		if(parent->lchild == oldone)
			parent->lchild = newone;
		else
			parent->rchild = newone;
		if(newone != nullptr)
			newone->parent = parent;
	}
	else
	{
		root = newone;
		if(root != nullptr)
			root->parent = nullptr;
	}
}
template<typename T>
void SpTree<T>::Remove(const T &vle)
{
	SpTreeNode<T> *parent,*trav;
	trav = root;
	while(trav != nullptr)
	{
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			break;
	}
	if(trav == nullptr)
		return;
	parent = trav->parent;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	{
		trav = trav->lchild;
		while(trav->rchild != nullptr)
			trav = trav->rchild;
		parent->data = trav->data;
		parent = trav;
	}
	if(trav->lchild != nullptr)
		replace_child(trav->lchild,trav,parent);
	else
		replace_child(trav->rchild,trav,parent);
	delete trav;
	count--;
}

template<typename T>
inline SpTreeNode<T>* SpTree<T>::first()
{
	SpTreeNode<T> *trav = root;
	if(trav->lchild != nullptr)
		trav = trav->lchild;
	return trav;
}

template<typename T>
inline SpTreeNode<T>* SpTree<T>::last()
{
	SpTreeNode<T> *trav = root;
	if(trav->rchild != nullptr)
		trav = trav->rchild;
	return trav;
}

template<typename T>
inline void SpTree<T>::rotatel(SpTreeNode<T> *&roo)
{
	SpTreeNode<T> *r;
	r = roo->rchild;
	replace_child(r,roo,roo->parent);
	roo->parent = r;
	roo->rchild = r->lchild;
	if(roo->rchild != nullptr)
		roo->rchild->parent = roo;
	r->lchild = roo;
	roo = r;
}

template<typename T>
inline void SpTree<T>::rotater(SpTreeNode<T> *&roo)
{
	SpTreeNode<T> *l;
	l = roo->lchild;
	replace_child(l,roo,roo->parent);
	roo->parent = l;
	roo->lchild = l->rchild;
	if(roo->lchild != nullptr)
		roo->lchild->parent = roo;
	l->rchild = roo;
	roo = l;
}
	
template<typename T>
SpTreeNode<T>* SpTree<T>::Search(const T &vle)
{
	SpTreeNode<T> *trav,*parent,*grandparent;
	trav = root;
	while(trav != nullptr)
	{
		if(trav->data == vle)
			break;
		else if(trav->data > vle)
			trav = trav->lchild;
		else
			trav = trav->rchild;
	}
	if(trav == nullptr)
		return nullptr;
	while(trav != root)
	{
		parent = trav->parent;
		grandparent = parent->parent;
		if(grandparent == nullptr)
		{
			if(parent->lchild == trav)
				rotater(parent);
			else
				rotatel(parent);
		}
		else
		{
			if(parent == grandparent->lchild && trav == parent->lchild)
			{
				rotater(grandparent);
				rotater(parent);
			}
			else if(parent == grandparent->rchild && trav == parent->rchild)
			{
				rotatel(grandparent);
				rotatel(parent);
			}
			else if(parent == grandparent->lchild && trav == parent->rchild)
			{
				rotatel(parent);
				rotater(grandparent);
			}
			else
			{
				rotater(parent);
				rotatel(grandparent);
			}
		}
	}
	return root;
}
#endif
