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
	friend	void Traverse_RF(TreeNode<T> *roo);
	public:
		Tree(){root = new TreeNode<T>;}
		~Tree(){if(!IsEmpty())Destory();}
		
		void CreateTree(TreeNode<T> *roo,std::istream &is);
		void SetFlag(const T &x,const T &y){isnextbrother = x;endm = y;}
		TreeNode<T>* Root(){return root;}
		// bool Parent();
		// bool FindParent(TreeNode<T> *roo,TreeNode<T> *p);
		TreeNode<T>* NextBrother(TreeNode<T> *p){if(p->nextbrother != nullptr) return p->nextbrother;else return nullptr;}
		// Tree<T>* NextT(){return nextt;}
		void Destory(){destroy(root);}//will be called by Forest class function.
		bool IsEmpty(){if(root != nullptr)return true;else return false;}
		bool Insert(T x);

		TreeNode<T> *root;
		Tree<T> *next;
		static T isnextbrother;
		static T endm;
		void destroy(TreeNode<T> *roo);
};

template<typename T> 
class Forest
{
	public:
	  void CreateForest(std::istream &is);
	  //bool RemoveTree(Tree<T> *);
	  BinTreeNode<T> *Tran2Bin();
	  Tree<T> *Build4Bin(BinTreeNode<T> *roo);
	  void DFS();
	  void BFS();

	  std::vector<TreeNode<T> *> head_link;

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
		while(tmp != roo && is>>vle)
		{
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
void Traverse_RF(TreeNode<T> *roo)
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
			Traverse_RF(p->firstchild);
			std::cout<<" ) ";
		}
		p = p->nextbrother;
	}
}
/*
 * 
 * template<typename T>
 * bool Tree<T>::FindParent(TreeNode<T> *roo,TreeNode<T> *p)
 * {
 *     TreeNode<T> *ro = roo->firstchild;
 *     bool succ;
 *     while( ro != nullptr && ro != p)
 *     {
 *         if((succ = FindParent(ro,p)) == true)
 *             return succ;
 *         ro = ro->nextbrother;
 *     }
 *     if(ro != nullptr && ro == p)
 *     {
 *         current = roo;
 *         return true;
 *     }
 *     else
 *     {
 *         current = nullptr;
 *         return false;
 *     }
 * }
 * template<typename T>
 * bool Tree<T>::Parent()
 * {
 *     TreeNode<T> *p = current;
 *     if(current == nullptr || current == root)
 *     {
 *         current = nullptr;
 *         return false;
 *     }
 *     return FindParent(root,p);
 * }
 */


// template<typename T>
// bool Forest<T>::RemoveTree(Tree<T> *p)
// {
// 	if(p == nullptr)
// 		return false;
// 	else
// 	{
// 		p->Destory();
// 		return true;
// 	}
// }

template<typename T>
void Forest<T>::CreateForest(std::istream &is)
{
	while (is)
	{
		TreeNode<T> *roo;
		CreateTree(roo, is);
		head_link.push_back(roo);
	}
}

template<typename T>
void Forest<T>::BFS()
{
	TreeNode<T> *p = *head_link.begin();
	while (p != nullptr)
	{
		Traverse_RF(p);
		std::cout<<std::endl;
		p++;
	}
}
#endif
