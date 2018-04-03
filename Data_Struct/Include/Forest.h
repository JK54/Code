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
#endif
