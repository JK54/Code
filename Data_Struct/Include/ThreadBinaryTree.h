#ifndef _THREAD_TREE_H
#define _THREAD_TREE_H

#include "sys_comm.h"
#include "BinaryTree.h"

template<typename T>
class ThreadTree;

template<typename T>
class BinTreeNode;

template <typename T>
class ThreadNode
{
	friend class ThreadTree<T>;
	private:
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

#endif