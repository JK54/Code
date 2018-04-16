#ifndef _FOREST_H
#define _FOREST_H

#include "sys_comm.h"
#include "BinaryTree.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "LinearList_linked_list.hpp"

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
	friend class Tree<T>;
	friend class Forest<T>;
	friend void Traverse_RootFirst<T>(TreeNode<T> *);
	friend void Traverse_RootLast<T>(TreeNode<T> *);
	private:
		T Data(){return data;}
		T data;
		TreeNode<T> *firstchild,*nextbrother;
		TreeNode(T value):data(value),firstchild(nullptr),nextbrother(nullptr){}
		TreeNode():firstchild(nullptr),nextbrother(nullptr){}
};

template<typename T>
class Tree
{
	friend class Forest<T>;
	friend void Traverse_RootFirst(TreeNode<T> *roo);
	public:
		Tree():root(new TreeNode<T>){}
		Tree(T vle):root(new TreeNode<T>(vle)){}
		~Tree(){if(!IsEmpty())Destory();}
		
		void CreateTree(TreeNode<T> *roo,std::istream &is);
		bool Search(TreeNode<T> *roo,const T &x);
		bool Insert(const T &vle);
		static void SetFlag(const T &x,const T &y){isnextbrother = x;endm = y;}
		TreeNode<T>* Root(){return root;}
		TreeNode<T>* NextBrother(TreeNode<T> *p){if(p->nextbrother != nullptr) return p->nextbrother;else return nullptr;}
		void Destory(){destroy(root);}//will be called by Forest class function.
		bool IsEmpty(){if(root == nullptr)return true;else return false;}
	private:
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
	  void CreateForest(std::istream &is);
	  BinTreeNode<T> *Tran2Bin();
	  Tree<T> *Build4Bin(BinTreeNode<T> *roo);
	  void DFS();
	  void BFS();

	private:
	  Queue<TreeNode<T>*> qroot;
};


template<typename T>
T Tree<T>::isnextbrother;
template<typename T>
T Tree<T>::endm;

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
	}
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
void Forest<T>::CreateForest(std::istream &is)
{
	Tree<T>::SetFlag(32767,0);
	while(is)
	{
		Tree<T> *p = new Tree<T>(0);
		qroot.Enqueue(p->root);
		p->CreateTree(p->root,is);
	}
}

template<typename T>
void Forest<T>::BFS()
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
#endif
