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
	AVLTreeNode():lchild(nullptr),rchild(nullptr),bf(0){}
	AVLTreeNode(T x):data(x),lchild(nullptr),rchild(nullptr),bf(0){}

	T Data(){return data;}
	private:
	T data;
	//Abbreviation for "balance factor",bf = Height(rchild) - Height(lchild).it only has values of -1,0,1
	int bf;	
	AVLTreeNode<T> *lchild;
	AVLTreeNode<T> *rchild;

};

template<typename T>
class AVLTree
{
	public:
		AVLTree():root(nullptr){}
		AVLTree(T x):root(new AVLTreeNode<T>(x)){}
		~AVLTree();

		AVLTreeNode<T>* Root(){return root;}
		void CreateTree(std::istream &is);
		AVLTreeNode<T>* Search(const T &vle) const;
		bool Insert(const T &vle);
		bool Remove(const T &vle);//need re-read it to make sure completely understanding.
		void Traverse(AVLTreeNode<T> *roo);
		void TraverseLevelOrder(AVLTreeNode<T> *roo);
	  private:
		AVLTreeNode<T> *root;
		
		void rotatel(AVLTreeNode<T> *&roo);//RR
		void rotater(AVLTreeNode<T> *&roo);//LL
		void rotatelr(AVLTreeNode<T> *&roo);//LR
		void rotaterl(AVLTreeNode<T> *&roo);//RL
		void destroy(AVLTreeNode<T> *roo);
		size_t height(AVLTreeNode<T> *roo);
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
}
	
template<typename T>
AVLTree<T>::~AVLTree()
{
	destroy(root);
}
	
template<typename T>
size_t AVLTree<T>::height(AVLTreeNode<T> *roo)
{
	if(roo == nullptr)
		return 0;
	size_t hl = height(roo->lchid);
	size_t hr = height(roo->rchild);
	size_t ht = hl > hr? hl + 1 : hr + 1;
	return ht;
}

template<typename T>
void AVLTree<T>::Traverse(AVLTreeNode<T> *roo)
{
	if(roo != nullptr)
	{
		Traverse(roo->lchild);
		std::cout<<roo->data<<" ";
		Traverse(roo->rchild);
	}
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
		Insert_NR(vle);
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::Search(const T &vle) const
{
	if(root == nullptr)
		return nullptr;
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
}
template<typename T>
void AVLTree<T>::rotatel(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *p = roo;
	roo = roo->rchild;
	p->rchild = roo->lchild;
	roo->lchild = p;
	roo->bf = p->bf = 0;
}

template<typename T>
void AVLTree<T>::rotater(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *p = roo;
	roo = roo->lchild;
	p->lchild = roo->rchild;
	roo->rchild = p;
	roo->bf = p->bf = 0;
}

template<typename T>
void AVLTree<T>::rotatelr(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *subL = roo->lchild;
	AVLTreeNode<T> *subR = roo;
	roo = subL->rchild;
	subL->rchild = roo->lchild;
	roo->lchild = subL;
	if(roo->bf <= 0)
		subL->bf = 0;
	else
		subL->bf = -1;
	subR->lchild = roo->rchild;
	roo->rchild = subR;
	if(roo->bf == -1 )
		subR->bf = 1;
	else
		subR->bf = 0;
	roo->bf = 0;
}

template<typename T>
void AVLTree<T>::rotaterl(AVLTreeNode<T> *&roo)
{
	AVLTreeNode<T> *subL = roo;
	AVLTreeNode<T> *subR = roo->rchild;
	roo = subR->lchild;
	subR->lchild = roo->rchild;
	roo->rchild = subR;
	if(roo->bf == - 1)
		subR->bf = 1;
	else
		subR->bf = 0;
	subL->rchild = roo->lchild;
	roo->lchild = subL;
	if(roo->bf == -1)
		subL->bf = 0;
	else
		subL->bf = -1;
	roo->bf = 0;
}

template<typename T>
bool AVLTree<T>::Insert(const T &vle)
{
	AVLTreeNode<T> *p = root;
	AVLTreeNode<T> *pr = nullptr;//parent of p.
	Stack<AVLTreeNode<T> *>s;//record of path of inserting.
	while(p != nullptr)
	{
		if(p->data == vle)//already exit in tree.
			return false;
		pr = p;
		s.Push(p);
		if(p->data > vle)
			p = p->lchild;
		else
			p = p->rchild;
	}
	p = new AVLTreeNode<T>(vle);
	if(pr == nullptr)
	{
		root = p;
		return true;
	}
	if(pr->data > p->data )
		pr->lchild = p;
	else
		pr->rchild = p;
	while(!s.IsEmpty())
	{
		s.Pop(pr);
		if(pr->lchild == p)
			pr->bf--;
		else
			pr->bf++;
		if(pr->bf == 0)
			break;
		else if(abs(pr->bf) == 1)
			p = pr;
		else
		{
			if(pr->bf*p->bf == 2 )//if p and pr have same sign
			{
				if(p->bf == 1)
					rotatel(pr);
				else
					rotater(pr);
			}
			else
			{
				if(p->bf == 1)
					rotatelr(pr);
				else
					rotaterl(pr);
			}
			break;
		}
	}
	if(s.IsEmpty())
		root = pr;
	else//the pointer of parent of pr have changed,need to relink it.Use p to receive the parent.
	{
		s.Pop(p);
		if(p->data > pr->data)
			p->lchild = pr;
		else
			p->rchild = pr;
	}
	return true;
}

template<typename T>
bool AVLTree<T>::Remove(const T &vle)
{
	AVLTreeNode<T> *p = root;
	AVLTreeNode<T> *pr = nullptr;
	AVLTreeNode<T> *q,*ppr;
	int d = 0 ,dd = 0;
	Stack<AVLTreeNode<T>*>s;
	while(p != nullptr)
	{
		if(p->data == vle)
			break;
		pr = p;
		s.Push(p);
		if(p->data > vle)
			p = p->lchild;
		else
			p = p->rchild;
	}
	if(p == nullptr)	
		return false;
	if(p->lchild != nullptr && p->rchild != nullptr)
	{
		pr = p;
		s.Push(pr);
		q = p->lchild;
		while(q->rchild != nullptr)
		{
			pr = q;
			s.Push(pr);
			q = q->rchild;
		}
		p->data = q->data;
		p = q;
	}
	if(p->lchild != nullptr)
		q = p->lchild;
	else
		q = p->rchild;
	if(pr == nullptr)
		root = q;
	else
	{
		if(pr->lchild == p)
			pr->lchild = q;
		else
			pr->rchild = q;
		while(!s.IsEmpty())
		{
			s.Pop(pr);
			if(pr->rchild == q)
				pr->bf--;
			else
				pr->bf++;
			if(!s.IsEmpty())
			{
				s.Top(ppr);
				dd = (ppr->lchild == pr)? -1 : 1;
			}
			else
				dd = 0;
			if(abs(pr->bf) == 1)
				break;
			if(pr->bf != 0)
			{
				if(pr->bf < 0)
				{
					d = -1;
					q = pr->lchild;
				}
				else
				{
					d = 1;
					q = pr->rchild;
				}
				if(q->bf == 0)
				{
					if(d == -1)
					{
						rotater(pr);
						pr->bf = 1;
						pr->lchild->bf = -1;
					}
					else
					{
						rotatel(pr);
						pr->bf = -1;
						pr->rchild->bf = 1;
					}
					break;
				}
				if(q->bf == d)
				{
					if(d == -1)
						rotater(pr);
					else
						rotatel(pr);
				}
				else
				{
					if(d == -1)
						rotatelr(pr);
					else
						rotaterl(pr);
				}
				if(dd == -1)
					ppr->lchild = pr;
				else
					ppr->rchild = pr;

			}
			q = pr;	
		}
		if(s.IsEmpty())	
			root = pr;
	}
	delete p;
	return true;
}
#endif
