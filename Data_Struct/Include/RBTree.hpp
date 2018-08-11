#ifndef _RBTREE_H
#define _RBTREE_H

#include "sys_comm.h"
#include "Stack.hpp"
#define RB_RED 0
#define RB_BLACK 1

//BSTree naturally use inorder as the permutation order.
template<typename T>
struct RBTreeNode
{
	RBTreeNode():lchild(nullptr),rchild(nullptr),parent(nullptr){};
	RBTreeNode(T x):value(x),color(RB_RED),lchild(nullptr),rchild(nullptr),parent(nullptr){};
	RBTreeNode(T x,bool cl):value(x),color(cl),lchild(nullptr),rchild(nullptr),parent(nullptr){};
	T value;
	bool color;
	RBTreeNode *lchild,*rchild,*parent;
};

template <typename T>
class RBTree
{
	public:
		RBTree():root(nullptr),count(0){};
		RBTree(T x):root(new RBTreeNode<T>(x,RB_BLACK)),count(1){};
		~RBTree();
		void CreatTree(T *data,const int &n);
		void CreatTree(std::istream &is);
		bool IsRBT();
		void Traverse(RBTreeNode<T> *roo);
		bool Search(const T &vle);
		bool Insert(const T &vle);
		bool Remove(const T &vle);
	private:
		RBTreeNode<T>* first();
		RBTreeNode<T>* last();
		RBTreeNode<T>* pre(RBTreeNode<T> *roo);
		RBTreeNode<T>* next(RBTreeNode<T> *roo);
		RBTreeNode<T>* grandparent(RBTreeNode<T> *roo);
		RBTreeNode<T>* uncle(RBTreeNode<T> *roo);
		size_t blacklength(RBTreeNode<T> *roo);
		void replace(RBTreeNode<T> *curr,RBTreeNode<T> *&pre);
		void rotatel(RBTreeNode<T> *roo);
		void rotater(RBTreeNode<T> *roo);
		void destroy(RBTreeNode<T> *roo);
		//-------member-----------
		RBTreeNode<T> *root;
		int count;
};

template<typename T>
void RBTree<T>::destroy(RBTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	if(roo->lchild != nullptr)
		destroy(roo->lchild);
	if(roo->rchild != nullptr)
		destroy(roo->rchild);
	delete roo;
	roo = nullptr;
}

template<typename T>
RBTree<T>::~RBTree<T>()
{
	destroy(root);
}

template<typename T>
bool RBTree<T>::IsRBT()
{
	//property 1 : a node is either red or black.
	RBTreeNode<T> *trav = root;
	Stack<int> len;
	Stack<RBTreeNode<T>*> path;
	int *blacklength = new int [count];
	int num = 0,length = 1;
	bool endmark = false,result = true;
	if(trav == nullptr)
		endmark =  true;
	//property 2 : root is black
	if(endmark == false && trav->GetColor() == RB_RED)
		endmark = true,result = false;
	while(endmark == false && (!path.IsEmpty() || trav != nullptr))
	{
		while(trav != nullptr)
		{
			if(trav->GetColor() == RB_BLACK)
				len.Push(++length);
			path.Push(trav);
			trav = trav->lchild;
		}
		if(!path.IsEmpty())
		{
			path.Pop(trav);
			len.Pop(length);
			std::cout<<trav->GetValue()<<" ";
			if(trav->lchild == nullptr || trav->rchild == nullptr)
			{
				//property 3 : all leave are black.
				blacklength[num++] = length + 1;
				//property 5 : every simple path has the same number of black nodes.
				if(blacklength[num - 1] != blacklength[0])
					endmark = true,result = false;
			}
			//property 4:both children of red nodes are blacks.
			if(trav->lchild != nullptr && trav->lchild->GetColor() == RB_RED &&  trav->GetColor() == RB_RED)
				endmark = true,result = false;
			if(trav->lchild != nullptr && trav->lchild->GetColor() == RB_RED && trav->GetColor() == RB_RED)
				endmark = true,result = false;
			trav = trav->rchild;
		}
	}
	delete [] blacklength;
	return result;
}
template<typename T>
RBTreeNode<T>* RBTree<T>::grandparent(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *gp;
	if(roo == root)
		gp = nullptr;
	else
		gp = roo->parent->parent;
	return gp;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::uncle(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *gp,uncle;
	if((gp = grandparent(roo)))
	{
		if(gp->rchild == roo->parent)
			uncle = gp->lchild;
		else
			uncle = gp->rchild;
	}
	else
		uncle = nullptr;
	return uncle;
}

template<typename T>
size_t RBTree<T>::blacklength(RBTreeNode<T> *roo)
{
	size_t height = 0;
	if(roo->lchild == nullptr || roo->rchild == nullptr)
		height++;
	while(roo->parent != nullptr)
		if(roo->color == RB_BLACK)
			height++;
	return height;
}
template<typename T>
RBTreeNode<T>* RBTree<T>::first()
{
	RBTreeNode<T> *roo;
	roo = root;
	while(roo->lchild != nullptr)
		roo = roo->lchild;
	return roo;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::last()
{
	RBTreeNode<T> *roo;
	roo = root;
	while(roo->rchild != nullptr)
		roo = roo->rchild;
	return roo;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::pre(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *trav;
	trav = roo;
	if(trav->lchild != nullptr)
	{
		trav = trav->lchild;
		while(trav->rchild != nullptr)
			trav = trav->rchild;
	}
	else
	{
		while(trav != root && trav == trav->parent->lchild)
			trav = trav->parent;
		trav = trav->parent;
	}
	return trav;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::next(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *trav;
	trav = roo;
	if(trav->rchild != nullptr)
	{
		trav = trav->rchild;
		while(trav->lchild != nullptr)
			trav = trav->lchild;
	}
	else
	{
		while(trav != root && trav == trav->parent->rchild)
			trav = trav->parent;
		trav = trav->parent;
	}
	return trav;
}

template<typename T>
void RBTree<T>::replace(RBTreeNode<T> *curr,RBTreeNode<T> *&pre)
{
	curr->lchild = pre->lchild;
	curr->rchild = pre->rchild;
	curr->parent = pre->parent;
	if(pre->lchild != nullptr)
		pre->lchild->parent = curr;
	if(pre->rchild != nullptr)
		pre->rchild->parent = curr;
	if(pre->parent != nullptr)
	{
		if(pre->parent->lchild == pre)
			pre->parent->lchild = curr;
		else
			pre->parent->rchild = curr;
	}
	else
		root = curr;
	delete pre;
	pre = nullptr;
}

template<typename T>
void RBTree<T>::rotatel(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *n,*rn,*rln;
	n = roo;
	rn = n->rchild;
	rln = rn->lchild;
	rn->lchild = n;
	rn->parent = n->parent;
	if(n->parent != nullptr)
	{
		if(n->parent->lchild == n)
			n->parent->lchild = rn;
		else
			n->parent->rchild = rn;
	}
	else
		root = rn;
	n->parent = rn;
	n->rchild = rln;
	if(rln != nullptr)
		rln->parent = n;
}

template<typename T>
void RBTree<T>::rotater(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *n,*ln,*lrn;
	n = roo;
	ln = n->lchild;
	lrn = ln->lchild;
	ln->rchild = n;
	ln->parent = n->parent;
	if(n->parent != nullptr)
	{
		if(n->parent->lchild == n)
			n->parent->lchild = ln;
		else
			n->parent->rchild = ln;
	}
	else
		root = ln;
	n->parent = ln;
	n->lchild = lrn;
	if(lrn != nullptr)
		lrn->parent = n;
}

template<typename T>
void RBTree<T>::Traverse(RBTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	Traverse(roo->lchild);
	std::cout<<roo->GetValue()<<" ";
	Traverse(roo->rchild);
}

template<typename T>
bool RBTree<T>::Search(const T &vle)
{
	RBTreeNode<T> *trav = root;
	while(trav != nullptr)
	{
		if(trav->GetValue() == vle)
			return true;
		else if(trav->GetValue() > vle)
			trav = trav->rchild;
		else
			trav = trav->lchild;
	}
	return false;
}

template<typename T>
bool RBTree<T>::Insert(const T &vle)
{
	RBTreeNode<T> *roo,*trav,*pre;
	trav = root;
	while(trav != nullptr)
	{
		pre = trav;
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
		{
			std::cout<<"repeating elements"<<std::endl;
			return false;
		}
	}
	trav = new RBTreeNode<T>(vle);
	if(pre == nullptr)
	{
		root = trav;
		root->color = RB_BLACK;
		return true;
	}
	if(pre->data > vle)
		pre->lchild = trav;
	else
		pre->rchild = trav;
	trav->parent = pre;
	while(trav != nullptr)
	{
	
	}
}
#endif
