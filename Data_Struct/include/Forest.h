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
		void Traverse_RF(TreeNode<T> *roo);

	private:
		TreeNode<T> *root;
		static T isnextbrother;
		static T endm;
		void destroy(TreeNode<T> *roo);
};

template<typename T> 
class Forest
{
	public:
		Forest();
		~Forest();

		Tree<T>* Head(){return head_list->head;}
		Tree<T>* Tail(){return head_list->tail;}
		void CreateForest(std::istream &is);
		bool RemoveTree(Tree<T> *);
		BinTreeNode<T> *Tran2Bin();
		Tree<T> *Build4Bin(BinTreeNode<T> *roo);
		void DFS();
		void BFS();
	private:
		LinkedList<Tree<T>*> head_list;
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
void Tree<T>::Traverse_RF(TreeNode<T> *roo)
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

template<typename T>
Forest<T>::Forest()
{
	head_list->head = head_list->tail = new Tree<T>;
}

template<typename T>
bool Forest<T>::RemoveTree(Tree<T> *p)
{
	if(p == nullptr)
		return false;
	else
	{
		p->Destory();
		return true;
	}
}

template<typename T>
Forest<T>::~Forest()
{
	while(head_list->head != nullptr)
	{
		Tree<T> *tmp = Head()->next;
		RemoveTree(head_list->head);
		Head() = tmp;
	}

}

template<typename T>
void Forest<T>::CreateForest(std::istream &is)
{
	while(is)	
	{
		head_list->tail->CreateTree(tail->Root(),is);
		if(is)
		{
			Tree<T> *tmp =  new Tree<T>;
			head_list->tail->next = tmp;
			head_list->
		}
	}
}

template<typename T>
void Forest<T>::BFS()
{
	Tree<T> *p = root;
	while(p != nullptr)
	{
		p->Traverse_RF(p->Root());
		std::cout<<std::endl;
		p = p->nextt;
	}
}
#endif
