#ifndef _BST_H
#define _BST_H

#include "BinaryTree.hpp"

template<typename T>
class BinTreeNode;

template<typename T>
class BinTree;

template<typename T>
class BSTree:public BinTree<T>
{
	public:
		BSTree():BinTree<T>(){};
		BSTree(T x):BinTree<T>(x){}
		~BSTree() = default;
		void CreateBST(std::istream &is);
};

template<typename T>
void BSTree<T>::CreateBST(std::istream &is)
{
	T data;
	while(is>>data)
	{
		BinTreeNode<T> *tmp = new BinTreeNode<T>(data);
		BinTreeNode<T> *roo = BinTree<T>::root;
		BinTreeNode<T> *preroo = nullptr;
		while(roo != nullptr)
		{
			preroo = roo;
			if(roo->data > data)
				roo = roo->lchild;
			else
				roo = roo->rchild;
		}
		if(data > preroo->data)
			preroo->rchild = tmp;
		else
			preroo->lchild = tmp;
	}
}
#endif
