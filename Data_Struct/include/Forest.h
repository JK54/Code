#ifndef _FOREST_H
#define _FOREST_H

#include "sys_comm.h"
#include "BinaryTree.h"
#include "Stack.h"
#include "Queue.h"
#include "LinearList_linked_list.h"

template<typename T>
struct TreeNode
{
		T Data(){return data;}
		T data;
		TreeNode<T> *firstchild,*nextbrother;
		// TreeNode(T value):data(value),firstchild(nullptr),nextbrother(nullptr){}
		TreeNode(T value = 0,TreeNode<T> *f = nullptr,TreeNode<T> *n = nullptr):data(value),firstchild(f),nextbrother(n){}
};

template<typename T>
class Tree
{
	public:
		Tree(){current = root = new TreeNode<T>;}
		~Tree(){if(!IsEmpty())Destory();}
		
		void SetFlag(T x,T y){isnextbrother = x;endm = y;}
		TreeNode<T>* Root(){return root;}
		TreeNode<T>* Parent(TreeNode<T> *p);
		TreeNode<T>* NextBrother(TreeNode<T> *p);
		void CreateTree(std::istream &is);
		void Destory(){destroy(root);}//will be called by Forest class function.
		bool IsEmpty(){if(root != nullptr)return true;else return false;}
		bool Insert(T x);
		void Traverse(TreeNode<T> *roo);

	private:
		TreeNode<T> *root,*current;
		static T isnextbrother;
		static T endm;
		void destroy(TreeNode<T> *roo);
};

template<typename T> 
class Forest
{
	public:
		bool RemoveTree(Tree<T> *);
	private:
		LinkedList<Tree<T>*> *root,*tail;
};

template<typename T>
T Tree<T>::isnextbrother;
template<typename T>
T Tree<T>::endm;


template<typename T>
void Tree<T>::destroy(TreeNode<T> *roo)
{
	
}

template<typename T>
void Tree<T>::CreateTree(std::istream &is)
{
	if(root == nullptr){std::cout<<"invalid initial node"<<std::endl;return;}
	else
	{
		T vle;
		TreeNode<T> *tmp;
		while(is>>vle)
		{
			if(current == root)
			{
				current->firstchild = new TreeNode<T>(vle);
				current = current->firstchild;
			}
			else
			{
				if(vle == isnextbrother && vle != endm)
				{
					is>>vle;
					current->nextbrother = new TreeNode<T>(vle);
					current = current->nextbrother;
				}
				else if(vle != isnextbrother && vle != endm)
				{
					current->firstchild = new TreeNode<T>(vle);
					tmp = current;
					current = current->firstchild;
					CreateTree(is);
					current = tmp;
				}
				else
				{
					return;
				}
			}
		}
	}
}
template<typename T>
void Tree<T>::Traverse(TreeNode<T> *roo)
{
	if(roo == nullptr)
	{
		return;
	}
	TreeNode<T> *p = roo;
	while(p != nullptr)
	{
		std::cout<<p->data<<" ";
		if(roo->firstchild != nullptr)
		{
			std::cout<<" ( ";
			Traverse(roo->firstchild);
			std::cout<<" ) ";
		}
		p = p->nextbrother;
	}
}

template<typename T>
TreeNode<T>* Tree<T>::Parent(TreeNode<T> *p)
{
	if(p == nullptr || p == root)
	{
		std::cout<<"p is nullptr or p is root node"<<std::endl;
		exit(1);
	}
	else
	{
		Queue<TreeNode<T>*> TNqueue;
		TreeNode<T> *trav = root->firstchild;
	}
}
#endif
