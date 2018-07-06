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
class TreeNode
{
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
		public:
	Tree():root(new TreeNode<T>){}
	Tree(T vle):root(new TreeNode<T>(vle)){}
	Tree(TreeNode<T> *roo):root(roo){}
	Tree(Tree<T> *p);
	~Tree(){if(!IsEmpty())Destory();}

	static void SetFlag(const T &x,const T &y);
	TreeNode<T>* Root();
	TreeNode<T>* NextBrother(TreeNode<T> *p);
	bool IsEmpty(){if(root == nullptr)return true;else return false;}
	void Destory(){destroy(root);}
	void CreateTree(TreeNode<T> *roo,std::istream &is);
	bool Search(TreeNode<T> *roo,const T &x);
	bool Insert(const T &vle);
	void Traverse_RootFirst(TreeNode<T> *roo);
	BinTreeNode<T>* Tran2Bint(TreeNode<T> *roo);
	TreeNode<T>* Build4Bint(BinTreeNode<T> *roo);
	void PrintBranch(TreeNode<T> *roo);
	private:
	TreeNode<T> *root;
	static T isnextbrother;
	static T endm;//the two static variable control the building of tree,just like genlist.
	void destroy(TreeNode<T> *roo);
	TreeNode<T>* copy(TreeNode<T> *);
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
		Tree<T>* SelectTree(const T &vle);
	private:
		Queue<Tree<T>*> qtree;//implicit call the contruct function of queue,so don't need to redefinite qtree.
		BinTreeNode<T>* root;
		void destroybintree(BinTreeNode<T> *roo);
};

//----------------------------definition of tree----------------------------------------------
template<typename T>
T Tree<T>::isnextbrother;
template<typename T>
T Tree<T>::endm;

template<typename T>
Tree<T>::Tree(Tree<T> *p)
{
	root = copy(p->root);
}

template<typename T>
TreeNode<T>* Tree<T>::copy(TreeNode<T> *p)
{
	if(p == nullptr)
		return nullptr;
	TreeNode<T> *tmp = new TreeNode<T>(p);
	tmp->firstchild = copy(p->firstchild);
	tmp->nextbrother = copy(p->nextbrother);
	return tmp;
}
template<typename T>
void Tree<T>::Traverse_RootFirst(TreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
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
	if(roo == nullptr)
	{
		std::cout<<"invalid initial node"<<std::endl;
		return;
	}
	else
	{
		T vle;
		is>>vle;
		//because root don't have a nextbrother object,so deal with root node before the loop.
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
			//the branch ends.
			else if(vle == Tree<T>::endm)
				s.Pop(tmp);
			//insert as first child as default
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
	if(Search(roo->firstchild,vle))
		return true;
	else
		return Search(roo->nextbrother,vle);
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
BinTreeNode<T>* Tree<T>::Tran2Bint(TreeNode<T> *roo)
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
TreeNode<T>* Tree<T>::Build4Bint(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return nullptr;
	TreeNode<T> *tmp = new TreeNode<T>(roo->data);
	tmp->firstchild = Build4Bint(roo->lchild);
	tmp->nextbrother = Build4Bint(roo->rchild);
	root = tmp;
	return tmp;
}

template<typename T>
void Tree<T>::PrintBranch(TreeNode<T> *roo)
{
	TreeNode<T> *ro;
	if(roo == nullptr)
		return;
	if(roo->firstchild != nullptr)
	{
		std::cout<<"("<<roo->data<<","<<roo->firstchild->data<<") ";
		PrintBranch(roo->firstchild);
	}
	if(roo->nextbrother != nullptr)
	{
		std::cout<<"("<<roo->data<<","<<roo->nextbrother->data<<") ";
		PrintBranch(roo->nextbrother);
	}
}
//-------------------------------forest definition-------------------------
	template<typename T>
void Forest<T>::CreateForest(std::istream &is)
{
	int i = 0;
	Tree<T> *p;
	while(is)
	{
		p = new Tree<T>(i);
		qtree.Enqueue(p);
		p->CreateTree(p->Root(),is);
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
	while(!qtree.IsEmpty())
	{
		Tree<T> *tmp;
		qtree.Dequeue(tmp);
		tmp->~Tree();
	}
	qtree.~Queue();
	destroybintree(root);
}
	template<typename T>
bool Forest<T>::RemoveTree(const T &vle)
{
	if(qtree.IsEmpty())
		return false;
	Tree<T> *tree;
	qtree.Dequeue(tree);
	Tree<T> *origintree = tree;
	if(tree->root->data == vle)
		return true;
	else
		qtree.Enqueue(tree);
	while(qtree.First() != origintree)
	{
		qtree.Dequeue(tree);
		if(tree->data == vle)
		{
			delete tree;
			while(qtree.First() != origintree)//keep origin sequence.
			{
				qtree.Dequeue(tree);
				qtree.Enqueue(tree);
			}
			return true;
		}
		else
			qtree.Enqueue(tree);
	}
	return false;// in case of the forest only contain one tree.
}

	template<typename T>
Tree<T>* Forest<T>::SelectTree(const T &vle)
{
	if(qtree.IsEmpty())
		return nullptr;
	Queue<Tree<T>*> tmpq;
	tmpq = qtree;
	Tree<T> *tmp;
	while(tmpq.Dequeue(tmp))
	{
		if(tmp->root->data == vle)
			return tmp;
	}
	return nullptr;
}
	template<typename T>
void Forest<T>::DFS()
{
	Queue<Tree<T>*> tmp = qtree;
	// tmp = qtree;
	Tree<T> *tree;
	while(tmp.Dequeue(tree))
	{
		tree->Traverse_RootFirst(tree->root);
		std::cout<<std::endl;
	}
}

	template<typename T>
void Forest<T>::BFS()
{
	if(qtree.IsEmpty())
		exit(1);
	Tree<T> *tree,*firsttree;
	TreeNode<T>* tmp;
	Queue<TreeNode<T>*> qnode;
	//enqueue the root node of trees.the tree queue can not directly used to traverse.
	qtree.Dequeue(firsttree);
	qnode.Enqueue(firsttree->Root());
	qtree.Enqueue(firsttree);
	while(qtree.First() != firsttree)
	{
		qtree.Dequeue(tree);
		qnode.Enqueue(tree->Root());
		qtree.Enqueue(tree);
	}
	//begin to traverse.
	while(!qnode.IsEmpty())
	{
		qnode.Dequeue(tmp);
		while(tmp != nullptr)
		{
			std::cout<<tmp->data<<" ";
			if(tmp->firstchild != nullptr)
				qnode.Enqueue(tmp->firstchild);
			tmp = tmp->nextbrother;
		}
	}
	std::cout<<std::endl;
}

template<typename T>
BinTreeNode<T>* Forest<T>::Tran2Bin()
{
	if(qtree.IsEmpty())
		return nullptr;
	BinTreeNode<T> *tmpb;
	Queue<BinTreeNode<T>*>broot;
	Queue<Tree<T>*> tmpqtree;
	tmpqtree = qtree;//copy qtree
	Tree<T> *tmpt;
	while(!tmpqtree.IsEmpty())
	{
		tmpqtree.Dequeue(tmpt);
		tmpb = tmpt->Tran2Bint(tmpt->root);
		// tmpb = new BinTreeNode<T>(tmpb2);
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
	return root;
}

template<typename T>
void Forest<T>::Build4Bin(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	Queue<BinTreeNode<T>*> broot;
	BinTreeNode<T>*tmpb = roo;
	Tree<T> *tree;
	while(tmpb != nullptr)
	{
		broot.Enqueue(tmpb);
		tmpb = tmpb->rchild;
	}
	while(!broot.IsEmpty())
	{
		broot.Dequeue(tmpb);
		tmpb->rchild = nullptr;
		tree->Build4Bint(tmpb);
		qtree.Enqueue(tree);
	}
}

#endif
