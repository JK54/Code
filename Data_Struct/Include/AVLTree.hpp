//It is impossible to heritage from BSTree,because you can not avoid one fatal question:you can not point to base class object with a derived class pointer.For example,if AVLTree heritaged from BinTreeNode,consider the statement: AVLTreeNode = AVLTreeNode::BinTreeNode::child.it can't be avoided.while,you can also said,i can using AVLTreeNode = AVLTreeNode::child,but it is bullshit,which only uselessly occupys memory space,and costs much time to consider how to use base class and derived part carefully,and still can not solve the problem,the derived private member "bf" of AVLTreeNode will be split when using base part.

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
		AVLTreeNode<T>* Search(const T &vle);
		void TraversePreOrder(AVLTreeNode<T> *roo);
		void TraverseInOrder(AVLTreeNode<T> *roo);
		void TraverseLevelOrder(AVLTreeNode<T> *roo);
		void UpdateHeight(AVLTreeNode<T> *&roo);
		size_t Count(){return count;}
	  private:
		void rebalance(AVLTreeNode<T> *&roo);
		void replace_child(AVLTreeNode<T>*&,AVLTreeNode<T>*&,AVLTreeNode<T>*&);
		int Height(AVLTreeNode<T> *&roo);
		int getbf(AVLTreeNode<T> *&roo);
		int max(size_t a,size_t b){return a > b ? a : b;}
		void rotatel(AVLTreeNode<T> *&roo);
		void rotater(AVLTreeNode<T> *&roo);
		void rotatelr(AVLTreeNode<T> *&roo);
		void rotaterl(AVLTreeNode<T> *&roo);
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
}
	
template<typename T>
AVLTree<T>::~AVLTree()
{
	destroy(root);
	root = nullptr;
	count = 0;
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
inline int AVLTree<T>::Height(AVLTreeNode<T> *&roo)
{
	return roo == nullptr ? 0 : roo->height;
}

template<typename T>
inline void AVLTree<T>::UpdateHeight(AVLTreeNode<T> *&roo)
{
	if(roo != nullptr)
		 roo->height = max(Height(roo->lchild),Height(roo->rchild)) + 1;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::Search(const T &vle)
{
	AVLTreeNode<T> *trav = root;
	while(trav != nullptr)
	{
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			return trav;
	}
	return trav;
}

template<typename T>
inline void AVLTree<T>::rotatel(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *r;
	r = roo->rchild;
	replace_child(r,roo,roo->parent);
	roo->parent = r;
	roo->rchild = r->lchild;
	if(roo->rchild != nullptr)
		roo->rchild->parent = roo;
	r->lchild = roo;
	UpdateHeight(roo);
	UpdateHeight(r);
	roo = r;
}

template<typename T>
inline void AVLTree<T>::rotater(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *l;
	l = roo->lchild;
	replace_child(l,roo,roo->parent);
	roo->parent = l;
	roo->lchild = l->rchild;
	if(roo->lchild != nullptr)
		roo->lchild->parent = roo;
	l->rchild = roo;
	UpdateHeight(roo);
	UpdateHeight(l);
	roo = l;
}

template<typename T>
inline void AVLTree<T>::rotatelr(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *l,*lr;
	l = roo->lchild;
	lr = l->rchild;
	replace_child(lr,roo,roo->parent);
	l->parent = lr;
	l->rchild = lr->lchild;
	if(l->rchild != nullptr)
		l->rchild->parent = l;
	roo->parent = lr;
	roo->lchild = lr->rchild;
	if(roo->lchild != nullptr)
		roo->lchild->parent = roo;
	lr->lchild = l;
	lr->rchild = roo;
	UpdateHeight(l);
	UpdateHeight(roo);
	UpdateHeight(lr);
	roo =  lr;
}

template<typename T>
inline void AVLTree<T>::rotaterl(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *r,*rl;
	r = roo->rchild;
	rl = r->lchild;
	replace_child(rl,roo,roo->parent);
	r->parent = rl;
	r->lchild = rl->rchild;
	if(r->lchild != nullptr)
		r->lchild->parent = r;
	roo->parent = rl;
	roo->rchild = rl->lchild;
	if(roo->rchild != nullptr)
		roo->rchild->parent =roo;
	rl->rchild = r;
	rl->lchild = roo;
	UpdateHeight(r);
	UpdateHeight(roo);
	UpdateHeight(rl);
	roo = rl;
}

template<typename T>
inline int AVLTree<T>::getbf(AVLTreeNode<T> *&roo)
{
	return Height(roo->rchild) - Height(roo->lchild);
}

template<typename T>
inline void AVLTree<T>::rebalance(AVLTreeNode<T> *&roo)
{
	size_t lh,rh,height;
	int bf,cbf;
	while(roo != nullptr)
	{
		lh = Height(roo->lchild);
		rh = Height(roo->rchild);
		height = max(lh,rh) + 1;
		bf = rh - lh;
		if(height != roo->height)
			UpdateHeight(roo);
		else if(bf >= -1 && bf <= 1)
			break;
		if(bf == -2)
		{
			cbf = getbf(roo->lchild);
			if(cbf == 1)
				rotatelr(roo);
			else
				rotater(roo);
		}
		else if(bf == 2)
		{
			cbf = getbf(roo->rchild) ;
			if(cbf == -1)
				rotaterl(roo);
			else
				rotatel(roo);
		}
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
inline void AVLTree<T>::replace_child(AVLTreeNode<T> *&n,AVLTreeNode<T> *&o,AVLTreeNode<T> *&p)
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
		if(root != nullptr)
			root->parent = nullptr;
	}
}
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
