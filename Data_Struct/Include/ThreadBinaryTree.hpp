#ifndef _THREAD_TREE_H
#define _THREAD_TREE_H

#include "sys_comm.h"
#include "BinaryTree.hpp"

template<typename T>
class ThreadTree;

template<typename T>
class BinTreeNode;

template <typename T>
class ThreadNode
{
	friend class ThreadTree<T>;
	T data;
	int ltag,rtag;
	ThreadNode<T> *lchild,*rchild;
	ThreadNode():ltag(0),rtag(0),lchild(nullptr),rchild(nullptr){}
	ThreadNode(T item):data(item),ltag(0),rtag(0),lchild(nullptr),rchild(nullptr){}
	ThreadNode(const BinTreeNode<T> *Bn);
};

template<typename T>
class ThreadTree
{
	public:
		ThreadTree(){root = new ThreadNode<T>;}
		ThreadTree(T item){root = new ThreadNode<T>(item);}
		~ThreadTree(){destroy(root);}

		void CreateInThread(BinTreeNode<T> *ro);
		void TraversePreOrder(ThreadNode<T> *roo);
		void TraverseInOrder(ThreadNode<T> *roo);
		void TraversePostOrder(ThreadNode<T> *current);
		ThreadNode<T>* Root(){return root;}
		ThreadNode<T>* First(ThreadNode<T> *current);
		ThreadNode<T>* Next(ThreadNode<T> *current);
		ThreadNode<T>* Last(ThreadNode<T> *current);
		ThreadNode<T>* Prior(ThreadNode<T> *current);
	private:
		ThreadNode<T> *root;

		ThreadNode<T>* buildthreadfrombin(ThreadNode<T> *ro,BinTreeNode<T> *roo);
		void destroy(ThreadNode<T> *roo);
		void visit(ThreadNode<T> *p){std::cout<<p->data<<" ";}
		ThreadNode<T> *parent(ThreadNode<T> *current);
		void CreateInThread(ThreadNode<T> *current,ThreadNode<T> *&pre);
};


	template<typename T>
ThreadNode<T>::ThreadNode(const BinTreeNode<T> *Bn)
{
	data = Bn->data;
	if(Bn->lchild == nullptr)
		ltag = 1;
	else
	{
		ltag = 0;
		lchild = new ThreadNode<T>(Bn->lchild->data);
	}
	if(Bn->rchild == nullptr)
		rtag = 1;
	else
	{
		rtag = 0;
		rchild = new ThreadNode<T>(Bn->rchild->data);
	}
}

	template<typename T>
void ThreadTree<T>::destroy(ThreadNode<T> *roo)
{
	if(roo == nullptr)
		return;
	else
	{
		ThreadNode<T> *ro = roo;
		ThreadNode<T> *tmp = First(ro);
		while(tmp != nullptr)
		{
			ro = Next(ro);
			delete tmp;
			tmp = ro;
		}
	}
}

	template<typename T>
ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current;
	while(p->ltag == 0)
		p = p->lchild;
	return p;
}

	template<typename T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current->rchild;
	if(current->rtag == 0)
		return First(p);
	else
		return p;
}

	template<typename T>
ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current;
	while(p->rtag == 0)
		p = p->rchild;
	return p;
}

	template<typename T>
ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current->lchild;
	if(current->ltag == 0)
		return Last(p);
	else
		return p;
}

	template<typename T>
ThreadNode<T>* ThreadTree<T>::buildthreadfrombin(ThreadNode<T> *ro,BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return nullptr;
	else
	{
		ro = new ThreadNode<T>(roo);
		ro->lchild = buildthreadfrombin(ro->lchild,roo->lchild);
		ro->rchild = buildthreadfrombin(ro->rchild,roo->rchild);
		return ro;
	}
}

	template<typename T>
void ThreadTree<T>::CreateInThread(ThreadNode<T> *current,ThreadNode<T> *&pre)
{
	if(current == nullptr)
		return;
	CreateInThread(current->lchild,pre);
	if(current->lchild == nullptr)
	{
		current->lchild = pre;
		current->ltag = 1;
	}
	if(pre != nullptr && pre->rchild == nullptr)
	{
		pre->rchild = current;
		pre->rtag = 1;
	}
	pre = current;
	CreateInThread(current->rchild,pre);
}

	template<typename T>
void ThreadTree<T>::CreateInThread(BinTreeNode<T> *ro)
{
	ThreadNode<T> *pre = nullptr;
	root = buildthreadfrombin(root,ro);
	if(root != nullptr)
	{
		CreateInThread(root,pre);
		pre->rchild = nullptr;
		pre->rtag = 1;
	}
}

	template<typename T>
void ThreadTree<T>::TraversePreOrder(ThreadNode<T> *current)
{
	if(current == nullptr)
		return;
	else
	{
		ThreadNode<T> *p = current;
		while(p != nullptr)
		{
			visit(p);
			if( p->ltag == 0)
				p = p->lchild;
			else if(p->rtag == 0)
				p = p->rchild;
			else
			{
				//when the leaf node comes to its ancestor which own lchild,change to the lchild.
				while(p != nullptr && p->rtag == 1)
					p = p->rchild;
				if( p != nullptr)
					p = p->rchild;
			}
		}
	}
}

	template<typename T>
void ThreadTree<T>::TraverseInOrder(ThreadNode<T> *roo)
{
	if(roo == nullptr)
		return;
	else
	{
		for(ThreadNode<T> *tmp = First(roo);tmp != nullptr;tmp =Next(tmp))
			std::cout<<tmp->data<<" ";
	}
}

	template<typename T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T> *current)
{
	if(current == root)
		return nullptr;
	ThreadNode<T> *p = current;
	while(p->ltag == 0)
		p= p->lchild;
	//there are 2 situation:
	//1.leap to the most left child,and jump to right.It does not be always successful when the current node is the left child of its parent.
	//2.leap to the most right child,jump tp left.
	if(p->lchild != nullptr)
	{
		p = p->lchild;
		while(p != nullptr && p->lchild != current && p->rchild != current)
			p = p->rchild;
	}
	if(p == nullptr || p->lchild == nullptr)
	{
		p = current;
		while(p->rtag == 0)
			p = p->rchild;
		p = p->rchild;
		while(p != nullptr && p->lchild != current && p->rchild != current)
			p = p->lchild;
	}
	return p;

}

	template<typename T>
void ThreadTree<T>::TraversePostOrder(ThreadNode<T> *current)
{
	if(current == nullptr)
		return;
	else
	{
		ThreadNode<T> *p = current;
		ThreadNode<T> *q;
		while(p->ltag == 0 || p->rtag == 0)
			if(p->ltag == 0)
				p = p->lchild;
			else if( p->rtag == 0)
				p = p->rchild;
		visit(p);
		while((q = parent(p)) != nullptr)
		{
			//if p is rchild of q,then it's time to visit "root"(q);Or the parent don't have a rchild,it also need to visit q.
			if (q->rchild == p || q->rtag == 1)
				p = q;
			// p is not the rchild of q
			else
			{
				p = q->rchild;
				while(p->ltag == 0 || p->rtag == 0)
					if(p->ltag == 0)
						p = p->lchild;
					else if( p->rtag == 0)
						p = p->rchild;
			}
			visit(p);
		}
	}
}
#endif
