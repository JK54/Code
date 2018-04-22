#ifndef _FOREST_H
#define _FOREST_H

#include "sys_comm.h"
#include "BinaryTree.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

template<typename T>
class TreeNode;

template<typename T>
class Tree;

template<typename T>
class Forest;

template<typename T>
void Traverse_RootFirst(TreeNode<T> *);

template<typename T>
void Traverse_RootLast(TreeNode<T> *);

template<typename T>
class TreeNode
{
	/*
	 * friend class Tree<T>;
	 * friend class Forest<T>;
	 * friend void Traverse_RootFirst<T>(TreeNode<T> *);
	 * friend void Traverse_RootLast<T>(TreeNode<T> *);//undo
	 */
	public:
	T Data(){return data;}
	TreeNode(T value):data(value),firstchild(nullptr),nextbrother(nullptr){}
	TreeNode():firstchild(nullptr),nextbrother(nullptr){}
	TreeNode(TreeNode<T> *roo):data(roo->data),firstchild(roo->firstchild),nextbrother(roo->nextbrother){}
	TreeNode(TreeNode<T> &roo):data(roo.data),firstchild(roo.firstchild),nextbrother(roo.nextbrother){}
	T data;
	TreeNode<T> *firstchild,*nextbrother;
};

template<typename T>
class Tree
{
	friend class Forest<T>;
	friend void Traverse_RootFirst(TreeNode<T> *roo);
	friend BinTreeNode<T>* Tran2Bint(TreeNode<T> *roo);
	friend TreeNode<T>* Tran4Bint(BinTreeNode<T> *roo);
	public:
	Tree():root(new TreeNode<T>){}
	Tree(T vle):root(new TreeNode<T>(vle)){}
	Tree(TreeNode<T> *roo):root(roo){}
	~Tree(){if(!IsEmpty())Destory();}

	static void SetFlag(const T &x,const T &y);
	TreeNode<T>* Root();
	TreeNode<T>* NextBrother(TreeNode<T> *p);
	bool IsEmpty(){if(root == nullptr)return true;else return false;}
	void Destory(){destroy(root);}
	void CreateTree(TreeNode<T> *roo,std::istream &is);
	bool Search(TreeNode<T> *roo,const T &x);
	bool Insert(const T &vle);
	// BinTreeNode<T>* Tran2Bin(TreeNode<T> *roo);
	TreeNode<T>* Tran4Bin(BinTreeNode<T> *roo);//only support the type of root of bintree only has lchild.in other words,tree->bintree->tree
	protected:
	TreeNode<T> *root;
	Tree<T> *next;
	static T isnextbrother;
	static T endm;//the two static variable control the building of tree,just like genlist.
	void destroy(TreeNode<T> *roo);
};

template<typename T>
class Forest
{
	public:
		Forest():root(new BinTreeNode<T>){}
		~Forest();
		void CreateForest(std::istream &is);
		BinTreeNode<T>* Tran2Bin();
		BinTreeNode<T> *Root() { return root; }
		void Build4Bin(BinTreeNode<T> *roo);
		void DFS();
		void BFS();
		bool RemoveTree(const T &vle);
		TreeNode<T>* SelectTree(const T &vle);
	private:
		Queue<TreeNode<T>*> qroot;//implicit call the contruct function of queue,so don't need to redefinite qroot.
		BinTreeNode<T>* root;
		void destroybintree(BinTreeNode<T> *roo);
};

//-----------------------------------------definition-----------------------------------------------------------
template<typename T>
T Tree<T>::isnextbrother;
template<typename T>
T Tree<T>::endm;

	template<typename T>
void Traverse_RootFirst(TreeNode<T> *roo)
{
	if(roo == nullptr)
	{
		return;
	}
	TreeNode<T> *p = roo;
	while(p != nullptr)
	{
		std::cout<<p->data<<" ";
		if(p->firstchild != nullptr)
		{
			std::cout<<" ( ";
			Traverse_RootFirst(p->firstchild);
			std::cout<<" ) ";
		}
		p = p->nextbrother;
	}
}
	template<typename T>
void Tree<T>::destroy(TreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	else
	{
		destroy(roo->nextbrother);
		destroy(roo->firstchild);
		delete roo;
		roo = nullptr;
	}
}

	template<typename T>
void Tree<T>::SetFlag(const T &x,const T &y)
{
	isnextbrother = x;
	endm = y;
}

	template<typename T>
TreeNode<T>* Tree<T>::Root()
{
	return root;
}

	template<typename T>
TreeNode<T>* Tree<T>::NextBrother(TreeNode<T> *p)
{
	if(p->nextbrother != nullptr)
		return p->nextbrother;
	else
		return nullptr;
}
	template<typename T>
void Tree<T>::CreateTree(TreeNode<T> *roo,std::istream &is)
{
	if(roo == nullptr){std::cout<<"invalid initial node"<<std::endl;return;}
	else
	{
		T vle;
		is>>vle;
		TreeNode<T> *tmp = new TreeNode<T>(vle);
		roo->firstchild = tmp;
		Stack<TreeNode<T>*>s;
		s.Push(tmp);
		while(!s.IsEmpty())
		{
			is>>vle;
			if(vle == Tree<T>::isnextbrother)
			{
				is>>vle;
				tmp->nextbrother = new TreeNode<T>(vle);
				tmp = tmp->nextbrother;
			}
			else if(vle == Tree<T>::endm)
				s.Pop(tmp);
			else
			{
				tmp->firstchild = new TreeNode<T>(vle);
				s.Push(tmp);
				tmp = tmp->firstchild;
			}
		}
	}
}

	template<typename T>
bool Tree<T>::Search(TreeNode<T> *roo,const T &vle)
{
	if(roo == nullptr)
		return false;
	if(roo->data == vle)
		return true;
	bool foundc = false,foundn = false;
	if(roo->firstchild != nullptr)
		foundc = Search(roo->firstchild,vle);
	if(roo->nextbrother != nullptr)
		foundn = Search(roo->nextbrother,vle);
	if(foundc || foundn)
		return true;
	else
		return false;
}

	template<typename T>
bool Tree<T>::Insert(const T &vle)
{
	if(IsEmpty())
		return false;
	if(!Search(root,vle))
	{
		TreeNode<T> *trav = root;
		TreeNode<T> *tmp = new TreeNode<T>(vle);
		while(trav->firstchild != nullptr)
			trav = trav->firstchild;
		while(trav->nextbrother != nullptr)
			trav = trav->nextbrother;
		trav->nextbrother = tmp;
		return true;
	}
	return false;
}

template<typename T>
BinTreeNode<T>* Tran2Bint(TreeNode<T> *roo)
{
	if(roo == nullptr)
		return nullptr;
	else
	{
		BinTreeNode<T> *tmp = new BinTreeNode<T>;
		tmp->data = roo->data;
		tmp->lchild = Tran2Bint(roo->firstchild);
		tmp->rchild = Tran2Bint(roo->nextbrother);//ps:tree root doesn't have a nextbrother.
		return tmp;
	}
}

	template<typename T>
TreeNode<T>* Tran4Bint(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return nullptr;
	TreeNode<T> *tmp = new TreeNode<T>(roo->data);
	tmp->firstchild = Tran4Bint(roo->lchild);
	tmp->nextbrother = Tran4Bint(roo->rchild);
	return tmp;
}

	template<typename T>
void Forest<T>::CreateForest(std::istream &is)
{
	Tree<T>::SetFlag(32767,0);
	int i = 0;
	while(is)
	{
		Tree<T> *p = new Tree<T>(i);
		qroot.Enqueue(p->root);
		p->CreateTree(p->root,is);
		i++;
	}
}

template<typename T>
void Forest<T>::destroybintree(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	destroybintree(roo->lchild);
	destroybintree(roo->rchild);
	delete roo;
	roo = nullptr;
}
template<typename T>
Forest<T>::~Forest()
{
	while(!qroot.IsEmpty())
	{
		TreeNode<T> *tmp;
		qroot.Dequeue(tmp);
		Tree<T> tmpt(tmp);
		tmpt.~Tree();
	}
	qroot.~Queue();
	destroybintree(root);
}
	template<typename T>
bool Forest<T>::RemoveTree(const T &vle)
{
	if(qroot.IsEmpty())
		return false;
	TreeNode<T> *roo;
	qroot.Dequeue(roo);
	TreeNode<T> *roof = roo;
	if(roo->data == vle)
		return true;
	else
		qroot.Enqueue(roo);
	while(qroot.First() != roof)
	{
		qroot.Dequeue(roo);
		if(roo->data == vle)
		{
			Tree<T> tmp(roo);
			delete tmp;
			while(qroot.First() != roof)//keep origin sequence.
			{
				qroot.Dequeue(roo);
				qroot.Enqueue(roo);
			}
			return true;
		}
		else
			qroot.Enqueue(roo);
	}
	return false;// in case of the forest only contain one tree.
}

	template<typename T>
TreeNode<T>* Forest<T>::SelectTree(const T &vle)
{
	if(qroot.IsEmpty())
		return nullptr;
	Queue<TreeNode<T>*> tmpq;
	TreeNode<T> *tmp;
	tmpq.Copy(qroot);
	while(tmpq.Dequeue(tmp))
	{
		if(tmp->data == vle)
			return tmp;
	}
	return nullptr;
}
	template<typename T>
void Forest<T>::DFS()
{
	Queue<TreeNode<T>*> tmpq;
	TreeNode<T> *roo;
	tmpq.Copy(qroot);
	while(tmpq.Dequeue(roo))
	{
		Traverse_RootFirst(roo);
		std::cout<<std::endl;
	}
}

	template<typename T>
void Forest<T>::BFS()
{
	Queue<TreeNode<T>*> tmpq;
	TreeNode<T>* tmp;
	tmpq.Copy(qroot);
	while(tmpq.Dequeue(tmp))
	{
		while(tmp != nullptr)
		{
			std::cout<<tmp->data<<" ";
			if(tmp->firstchild != nullptr)
				tmpq.Enqueue(tmp->firstchild);
			if(tmp->nextbrother != nullptr)
				tmp = tmp->nextbrother;
			else
				break;
		}
	}
	std::cout<<std::endl;
}

template<typename T>
BinTreeNode<T>* Forest<T>::Tran2Bin()
{
	if(qroot.IsEmpty())
		return nullptr;
	BinTreeNode<T> *tmpb;
	Queue<BinTreeNode<T>*>broot;
	Queue<TreeNode<T>*> tmpqroot;//copy qroot
	tmpqroot.Copy(qroot);
	TreeNode<T> *tmpt;
	while(!tmpqroot.IsEmpty())
	{
		tmpqroot.Dequeue(tmpt);
		BinTreeNode<T> *tmpb2 = Tran2Bint(tmpt);
		tmpb = new BinTreeNode<T>(tmpb2);
		broot.Enqueue(tmpb);
	}
	broot.Dequeue(tmpb);
	BinTreeNode<T> *roo;
	roo = root = tmpb;
	while(broot.Dequeue(tmpb))
	{
		roo->rchild = tmpb;
		roo = roo->rchild;
	}
	roo = root;
	return roo;
}

template<typename T>
void Forest<T>::Build4Bin(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	Queue<BinTreeNode<T>*> broot;
	BinTreeNode<T>*tmpb = roo;
	while(tmpb != nullptr)
	{
		broot.Enqueue(tmpb);
		tmpb = tmpb->rchild;
	}
	while(!broot.IsEmpty())
	{
		broot.Dequeue(tmpb);
		tmpb->rchild = nullptr;
		TreeNode<T> *tmp = Tran4Bint(tmpb);
		qroot.Enqueue(tmp);
	}
}
#endif
