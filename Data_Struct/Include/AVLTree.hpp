//It is impossible to heritage from BSTree,because you can not avoid one fatal question:you can not point to base class object with a derived class pointer.For example,if AVLTree heritaged from BinTreeNode,consider the statement: AVLTreeNode = AVLTreeNode::BinTreeNode::child.it can't be avoided.while,you can also said,i can using AVLTreeNode = AVLTreeNode::child,but it is bullshit,which only uselessly occupys memory space,and costs much time to consider how to use base class and derived part carefully,and still can not solve the problem,the derived private member "bf" of AVLTreeNode will be split when using base part.

//optimization direction:
//1.replace():just transfer the value from the trav to pre,and delete trav node,then the most part of re-link work can be avoided.
#ifndef _AVLTree_H
#define _AVLTree_H

#include "sys_comm.h"
#include "Stack.hpp"
#include "Queue.hpp"

template<typename T>
class AVLTree;

template<typename T>
class AVLTreeNode
{
	friend class AVLTree<T>;
	public:
	AVLTreeNode():height(1),parent(this),lchild(nullptr),rchild(nullptr){}
	AVLTreeNode(T x):data(x),height(1),parent(this),lchild(nullptr),rchild(nullptr){}
	T Data(){return data;}
	private:
	T data;
	int height;
	AVLTreeNode<T> *parent;
	AVLTreeNode<T> *lchild;
	AVLTreeNode<T> *rchild;
};

template<typename T>
class AVLTree
{
	public:
		AVLTree(){root = nullptr;count = 0;}
		AVLTree(T x){root(new AVLTreeNode<T>(x));root->parent = nullptr;count = 1;}
		~AVLTree();

		AVLTreeNode<T>* Root(){return root;}
		void CreateTree(std::istream &is);
		void CreateTree(T *data,int n);
		bool Insert(const T &vle);
		bool Remove(const T &vle);
		bool Search(const T &vle);
		void TraversePreOrder(AVLTreeNode<T> *roo);
		void TraverseInOrder(AVLTreeNode<T> *roo);
		void TraverseLevelOrder(AVLTreeNode<T> *roo);
		inline void UpdateHeight(AVLTreeNode<T> *roo);
		void PrintCount(){std::cout<<count<<std::endl;}
	  private:
		void rebalance(AVLTreeNode<T> *roo);
		// void replace(AVLTreeNode<T>*,AVLTreeNode<T>*);
		inline void replace_child(AVLTreeNode<T>*,AVLTreeNode<T>*,AVLTreeNode<T>*);
		inline size_t Height(AVLTreeNode<T> *roo);
		inline void setparent(AVLTreeNode<T> *,AVLTreeNode<T> *);
		inline AVLTreeNode<T>* fix_l(AVLTreeNode<T> *roo);
		inline AVLTreeNode<T>* fix_r(AVLTreeNode<T> *roo);
		AVLTreeNode<T>* rotatel(AVLTreeNode<T> *roo);
		AVLTreeNode<T>* rotater(AVLTreeNode<T> *roo);
		AVLTreeNode<T>* rotatelr(AVLTreeNode<T> *roo);
		AVLTreeNode<T>* rotaterl(AVLTreeNode<T> *roo);
		void destroy(AVLTreeNode<T> *roo);
		//member
		AVLTreeNode<T> *root;
		size_t count;
};

template<typename T>
void AVLTree<T>::destroy(AVLTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	destroy(roo->lchild);
	destroy(roo->rchild);
	delete roo;
	roo = nullptr;
	count = 0;
}
	
template<typename T>
AVLTree<T>::~AVLTree()
{
	destroy(root);
	root = nullptr;
}

template<typename T>
void AVLTree<T>::TraversePreOrder(AVLTreeNode<T> *roo)
{
	if(roo != nullptr)
	{
		std::cout<<roo->data<<" ";
		TraversePreOrder(roo->lchild);
		TraversePreOrder(roo->rchild);
	}
}

template<typename T>
void AVLTree<T>::TraverseInOrder(AVLTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	TraverseInOrder(roo->lchild);
	std::cout<<roo->data<<" ";
	TraverseInOrder(roo->rchild);
}
template<typename T>
void AVLTree<T>::TraverseLevelOrder(AVLTreeNode<T> *roo)
{
	Queue<AVLTreeNode<T>*> q;
	AVLTreeNode<T> *trav;
	if(roo == nullptr)
	{
		std::cerr<<"empty tree,can not traverse"<<std::endl;
		exit(1);
	}
	else
		q.Enqueue(roo);
	while(!q.IsEmpty())
	{
		q.Dequeue(trav);
		std::cout<<trav->data<<" ";
		if(trav->lchild != nullptr)
			q.Enqueue(trav->lchild);
		if(trav->rchild != nullptr)
			q.Enqueue(trav->rchild);
	}
}

template<typename T>
void AVLTree<T>::CreateTree(std::istream &is)
{
	T vle;
	while(is>>vle)
		Insert(vle);
}

template<typename T>
void AVLTree<T>::CreateTree(T *data,int n)
{
	for(int i = 0;i < n;i++)
		Insert(data[i]);
}

template<typename T>
inline size_t AVLTree<T>::Height(AVLTreeNode<T> *roo)
{
	if(roo == nullptr)
		return 0;
	size_t lh = roo->lchild == nullptr ? 0 : roo->lchild->height;
	size_t lr = roo->rchild == nullptr ? 0 : roo->rchild->height;
	return std::max(lh,lr) + 1;
}

template<typename T>
inline void AVLTree<T>::UpdateHeight(AVLTreeNode<T> *roo)
{
	if(roo != nullptr)
		roo->height = Height(roo);
}

template<typename T>
bool AVLTree<T>::Search(const T &vle)
{
	AVLTreeNode<T> *trav;
	trav = root;
	while(trav != nullptr)
	{
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			return true;
	}
	return false;
}

template<typename T>
inline void AVLTree<T>::setparent(AVLTreeNode<T> *roo,AVLTreeNode<T> *parent)
{
	if(roo != nullptr)
		roo->parent = parent;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotatel(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *r;
	r = roo->rchild;
	replace_child(r,roo,roo->parent);
	roo->parent = r;
	roo->rchild = r->lchild;
	setparent(roo->rchild,roo);
	r->lchild = roo;
	UpdateHeight(roo);
	UpdateHeight(r);
	return r;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotater(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *l;
	l = roo->lchild;
	replace_child(l,roo,roo->parent);
	roo->parent = l;
	roo->lchild = l->rchild;
	setparent(roo->lchild,roo);
	l->rchild = roo;
	UpdateHeight(roo);
	UpdateHeight(l);
	return l;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotatelr(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *l,*lr;
	l = roo->lchild;
	lr = l->rchild;
	replace_child(lr,roo,roo->parent);
	l->parent = lr;
	l->rchild = lr->lchild;
	setparent(l->rchild,l);
	roo->parent = lr;
	roo->lchild = lr->rchild;
	setparent(roo->lchild,roo);
	lr->lchild = l;
	lr->rchild = roo;
	UpdateHeight(l);
	UpdateHeight(roo);
	UpdateHeight(lr);
	return lr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotaterl(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *r,*rl;
	r = roo->rchild;
	rl = r->lchild;
	replace_child(rl,roo,roo->parent);
	r->parent = rl;
	r->lchild = rl->rchild;
	setparent(r->lchild,r);
	roo->parent = rl;
	roo->rchild = rl->lchild;
	setparent(roo->rchild,roo);
	rl->rchild = r;
	rl->lchild = roo;
	UpdateHeight(r);
	UpdateHeight(roo);
	UpdateHeight(rl);
	return rl;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::fix_l(AVLTreeNode<T> *roo)
{
	int lbf = Height(roo->lchild->rchild) - Height(roo->lchild->lchild);
	if(lbf == 1)
		return rotatelr(roo);
	else
		return rotater(roo);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::fix_r(AVLTreeNode<T> *roo)
{
	int rbf = Height(roo->rchild->rchild) - Height(roo->rchild->lchild);
	if(rbf == -1)
		return rotaterl(roo);
	else
		return rotatel(roo);
}

template<typename T>
void AVLTree<T>::rebalance(AVLTreeNode<T> *roo)
{
	size_t lh,rh,height;
	int bf;
	while(roo != nullptr)
	{
		height = Height(roo);
		lh = Height(roo->lchild);
		rh = Height(roo->rchild);
		bf = rh - lh;
		if(height != roo->height)
			UpdateHeight(roo);
		else if(bf >= -1 && bf <= 1)
			break;
		if(bf == -2)
			roo = fix_l(roo);
		else if(bf == 2)
			roo = fix_r(roo);
		roo = roo->parent;
	}
}
template<typename T>
bool AVLTree<T>::Insert(const T &vle)
{
	AVLTreeNode<T> *pre,*trav;
	pre = nullptr;
	trav = root;
	while(trav != nullptr)
	{
		pre = trav;
		if(trav->data >vle)	
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			return false;
	}
	trav = new AVLTreeNode<T>(vle);
	trav->parent = pre;
	if(pre == nullptr)
		root = trav;
	else
	{
		if(pre->data > vle)
			pre->lchild = trav;
		else
			pre->rchild = trav;
		rebalance(pre);
	}
	count++;
	return true;
}

template<typename T>
inline void AVLTree<T>::replace_child(AVLTreeNode<T> *n,AVLTreeNode<T> *o,AVLTreeNode<T> *p)
{
	if(p != nullptr)
	{
		if(p->lchild == o)
			p->lchild = n;
		else
			p->rchild = n;
		if(n != nullptr)
			n->parent = p;
	}
	else
	{
		root = n;
		setparent(n,nullptr);
	}
}
//basic logic:find the node wanted to delete,and find the alternative node to replace the node,relink the pointer,if the node is root,then the root node should change.
template<typename T>
bool AVLTree<T>::Remove(const T &vle)
{
	AVLTreeNode<T> *trav,*pre,*parent;
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
		return false;
	pre = trav;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	{
		trav = trav->lchild;
		while(trav->rchild != nullptr)
			trav = trav->rchild;
		pre->data = trav->data;
		pre = trav;
	}
	if(trav->lchild != nullptr)
		trav = trav->lchild;
	else
		trav = trav->rchild;
	parent = pre->parent;
	replace_child(trav,pre,parent);
	delete pre;
	if(parent != nullptr)
		rebalance(parent);
	count--;
	return true;
}	
#endif
