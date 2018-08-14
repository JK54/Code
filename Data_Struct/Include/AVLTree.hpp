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
		void UpdateHeight(AVLTreeNode<T> *roo);
		void PrintCount(){std::cout<<count<<std::endl;}
	  private:
		AVLTreeNode<T>* search(const T &vle);
		int getbf(AVLTreeNode<T> *roo);
		void rebalance(AVLTreeNode<T> *roo);
		void replace(AVLTreeNode<T>*,AVLTreeNode<T>*);
		void replace2(AVLTreeNode<T>*,AVLTreeNode<T>*);
		size_t Height(AVLTreeNode<T> *roo);
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
size_t AVLTree<T>::Height(AVLTreeNode<T> *roo)
{
	if(roo == nullptr)
		return 0;
	size_t lh = roo->lchild == nullptr ? 0 : roo->lchild->height;
	size_t lr = roo->rchild == nullptr ? 0 : roo->rchild->height;
	return std::max(lh,lr) + 1;
}

template<typename T>
void AVLTree<T>::UpdateHeight(AVLTreeNode<T> *roo)
{
	if(roo != nullptr)
		roo->height = Height(roo);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::search(const T &vle)
{
	AVLTreeNode<T> *pre,*trav;
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
			return trav;
	}
	return pre;
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
AVLTreeNode<T>* AVLTree<T>::rotatel(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *r;
	r = roo->rchild;
	roo->rchild = r->lchild;
	if(root == roo)
	{
		root = r;
		root->parent = nullptr;
	}
	else
	{
		r->parent = roo->parent;
		if(roo->parent->lchild == roo)
			roo->parent->lchild = r;
		else
			roo->parent->rchild = r;
	}
	if(r->lchild != nullptr)
		r->lchild->parent = roo;
	r->lchild = roo;
	roo->parent = r;
	UpdateHeight(roo);
	UpdateHeight(r);
	return r;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotater(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *l;
	l = roo->lchild;
	roo->lchild = l->rchild;
	if(root == roo)
	{
		root = l;
		root->parent = nullptr;
	}
	else
	{
		l->parent = roo->parent;
		if(roo->parent->lchild == roo)
			roo->parent->lchild = l;
		else
			roo->parent->rchild = l;
	}
	if(l->rchild != nullptr)
		l->rchild->parent = roo;
	l->rchild = roo;
	roo->parent = l;
	UpdateHeight(roo);
	UpdateHeight(l);
	return l;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotatelr(AVLTreeNode<T> *roo)
{
	rotatel(roo->lchild);
	return rotater(roo);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rotaterl(AVLTreeNode<T> *roo)
{
	rotater(roo->rchild);
	return rotatel(roo);
}

template<typename T>
int AVLTree<T>::getbf(AVLTreeNode<T> *roo)
{
	if(roo == nullptr)
		return 0;
	size_t lh = roo->lchild == nullptr ? 0 : roo->lchild->height;
	size_t lr = roo->rchild == nullptr ? 0 : roo->rchild->height;
	return lr - lh;
}
template<typename T>
void AVLTree<T>::rebalance(AVLTreeNode<T> *roo)
{
	AVLTreeNode<T> *pre = roo;
	int tmph,bf_pre,bf_trav;
	bf_pre = bf_trav = 0;
	tmph = Height(pre);
	//the last two condition are compatible for remove procedure,and the last make sure the loop run at least once.
	while(pre->height != tmph || abs(bf_pre) == 2 || bf_trav == 0)
	{
		UpdateHeight(pre);
		if(abs(bf_pre) == 2)
		{
			if(bf_pre == 2 && (bf_trav == 1 || bf_trav == 0))
				pre = rotatel(pre);
			else if(bf_pre == -2 && (bf_trav == -1 || bf_trav == 0))
				pre = rotater(pre);
			else if(bf_pre == 2 && bf_trav == -1)
				pre = rotaterl(pre);
			else
				pre = rotatelr(pre);
		}
		bf_trav = getbf(pre);
		//for remove
		if(bf_trav == 0)
		{
			if(pre == root);
			else if(pre->parent->lchild == pre)
				bf_trav = getbf(pre->parent->rchild);
			else
				bf_trav = getbf(pre->parent->lchild);
		}
		else if(abs(bf_trav) == 2)
		{
			bf_pre = bf_trav;
			if(bf_trav == 2)
				bf_trav = getbf(pre->rchild);
			else
				bf_trav = getbf(pre->lchild);
			continue;
		}
		//for remove ended
		pre = pre->parent;
		if(pre == nullptr)
			break;
		tmph = Height(pre);
		bf_pre = getbf(pre);
	}
}

template<typename T>
bool AVLTree<T>::Insert(const T &vle)
{
	AVLTreeNode<T> *pre,*trav;
	pre = search(vle);
	trav = new AVLTreeNode<T>(vle);
	trav->parent = pre;
	if(pre == nullptr)
	{
		root = trav;
		root->parent = nullptr;
		count++;
		return true;
	}
	if(pre->data == vle)
	{
		delete trav;
		return false;
	}
	if(trav->data > pre->data)
		pre->rchild = trav;
	else
		pre->lchild = trav;
	rebalance(pre);
	count++;
	return true;
}

template<typename T>
void AVLTree<T>::replace(AVLTreeNode<T> *trav,AVLTreeNode<T> *pre)
{
	if(trav != nullptr)
	{
		trav->parent = pre->parent;
		if(pre->lchild != trav)
			trav->lchild = pre->lchild;
		if(pre->rchild != trav)
			trav->rchild = pre->rchild;
		UpdateHeight(trav);
		if(trav->lchild != nullptr)
			trav->lchild->parent = trav;
		if(trav->rchild != nullptr)
			trav->rchild->parent = trav;
	}
	//handle root
	if(root != pre)
	{
		if(pre->parent->lchild == pre)
			pre->parent->lchild = trav;
		else
			pre->parent->rchild = trav;
	}
	else
		root = trav;
	delete pre;
	pre = nullptr;
}

//basic logic:find the node wanted to delete,and find the alternative node to replace the node,relink the pointer,if the node is root,then the root node should change.
template<typename T>
bool AVLTree<T>::Remove(const T &vle)
{
	AVLTreeNode<T> *trav,*pre,*tmp;
	trav = search(vle);
	if(trav == nullptr || trav->data != vle)
		return false;
	pre = trav;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	{
		trav = trav->lchild;
		while(trav->rchild != nullptr)
			trav = trav->rchild;
		tmp = trav->parent;
		//wanted node is root and the deep of path of trav is 1.
		if(pre == tmp)
			tmp = trav;
		else
		{
			//change the link relation between tmp(parent of trav) and its grandson,the grandson become the direct son of tmp.
			tmp->rchild = trav->lchild;
			if(trav->lchild != nullptr)
				trav->lchild->parent = tmp;
		}
	}
	else
	{
		if(trav->lchild != nullptr)
			trav = trav->lchild;
		else
			trav = trav->rchild;
		tmp = pre->parent;
	}
	replace(trav,pre);
	//the situations of nullptr tmp:1.the wanted node is root and only has one branch child,then we dont need to rebalance the tree.2.the wanted node is the last node of tree.we jump it in these situations.
	if(tmp != nullptr)
		rebalance(tmp);
	count--;
	return true;
}	
#endif
