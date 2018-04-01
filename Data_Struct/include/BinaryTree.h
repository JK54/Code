#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "sys_comm.h"
#include "Stack.h"
#include "Queue.h"

template<typename T>
class BinTreeNode
{
	public:
		T data;
		BinTreeNode<T> *lchild;
		BinTreeNode<T> *rchild;
		BinTreeNode():lchild(nullptr),rchild(nullptr){}
		BinTreeNode(T x):data(x),lchild(nullptr),rchild(nullptr){}
};

template<typename T>
class BinTree
{
	friend void CreateTreePreOrder(BinTreeNode<T> *&ro,std::istream &is);
	//reconsider the situation:there are some nodes have the same value.
	//In some case,replicated elements can build mutiple binarytree.
	//e.g:inorder:2111211,postorder:2121111,it can be 1( 2 1( 1( 1 2) 1) or 1( 1(2) 1(1(2 1)))
	//Maybe there is a algorithm to build all cases of trees,remains to be solved.
	friend BinTreeNode<T>* CreateTreeByPreInOrder(T *preo,T *ino,int n);
	friend BinTreeNode<T>* CreateTreeByInPostOrder(T *ino,T *posto,int n);
	friend std::set<BinTreeNode<T>*> CreateTreeByInPostOrder_Duplicated(T *ino,T *posto,int n);
	public:
		static T endm;

		BinTree();
		BinTree(T x);
		~BinTree();
		BinTree(const BinTree<T> &s);

		bool operator==(const BinTree<T> &s);
		bool operator!=(const BinTree<T> &s);//in fact,the opposite value of "==".
		BinTree<T>& operator=(const BinTree<T> &s);
		
		//get root node and modify endmark
		BinTreeNode<T>* Root(){return root;}
		void SetMark(T x){endm = x;}
		//recursive traverse
		//bool type variable "ingen" control the output in genlist format or not
		void TraversePreOrder(BinTreeNode<T> *ro,bool ingen);
		void TraverseInOrder(BinTreeNode<T> *ro);
		void TraversePostOrder(BinTreeNode<T> *ro);
		//no-recursive traverse
		void TraversePreOrder_NR1(BinTreeNode<T> *roo);
		void TraversePreOrder_NR2(BinTreeNode<T> *roo);
		void TraversePreOrder_NR3(BinTreeNode<T> *roo);
		void TraverseInOrder_NR(BinTreeNode<T> *roo);
		void TraversePostOrder_NR(BinTreeNode<T> *roo);
		void TraverseLevelOrder(BinTreeNode<T> *roo);
	
		//use traverse to complete
		size_t Height();
		size_t Size();
		BinTreeNode<T>* Copy(BinTreeNode<T> *orign);
		bool Equal(BinTreeNode<T> *l,BinTreeNode<T> *r);

	private:
		BinTreeNode<T> *root;
		size_t *use;//the binary tree use count,control the distructor.
		void destroy(BinTreeNode<T> *ro);
};


#endif
