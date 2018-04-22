#ifndef _BSTree_H
#define _BSTree_H

#include "BinaryTree.hpp"

template<typename T>
class BSTree:public BinTree<T>
{
	public:
		BSTree():BinTree<T>(){}
		BSTree(T x):BinTree<T>(x){}
		virtual ~BSTree() = default;

		void CreateTree(std::istream &is);
		bool Insert(const T &vle);
		bool Remove_NR(const T &vle);
		bool Search(const T &vle);
		bool Remove(const T &vle,BinTreeNode<T> *&roo);//only support for the BSTree,not for AVLTree.
};
//--------------------------------------BSTree------------------------------------------

	template<typename T>
void BSTree<T>::CreateTree(std::istream &is)
{
	T data;
	while(is>>data)
		Insert(data);
}

	template<typename T>
bool BSTree<T>::Insert(const T &vle)
{
	BinTreeNode<T> *tmp = new BinTreeNode<T>(vle);
	BinTreeNode<T> *roo = BinTree<T>::root;
	while(roo != nullptr)
	{
		if(roo->data > vle)
		{
			if(roo->lchild != nullptr)
				roo = roo->lchild;
			else
				break;
		}
		else if(roo->data < vle)
		{
			if(roo->rchild != nullptr)
				roo = roo->rchild;
			else
				break;
		}
		else
		{
			std::cerr<<"repeating element.."<<std::endl;
			return false;
		}
	}
	if(vle > roo->data)
		roo->rchild = tmp;
	else
		roo->lchild = tmp;
	return true;
}

	template<typename T>
bool BSTree<T>::Search(const T &vle)
{
	if(BinTree<T>::root == nullptr)
	{
		std::cout<<"empty tree..."<<std::endl;
		return false;
	}
	BinTreeNode<T> *tmp = BinTree<T>::root;
	while(tmp->data != vle)
	{
		if(tmp->data > vle && tmp->lchild != nullptr)
			tmp = tmp->lchild;
		else if(tmp->data < vle && tmp->rchild != nullptr)
			tmp = tmp->rchild;
		else
			return false;
	}
	return true;
}

	template<typename T>
bool BSTree<T>::Remove_NR(const T &vle)
{
	if(Search(vle) == false)
		return false;
	else
	{
		BinTreeNode<T> *tmp = BinTree<T>::root;
		BinTreeNode<T> *pretmp = tmp;
		int lc;
		while(tmp->data != vle)//vle is element of bst
		{
			pretmp = tmp;
			if(tmp->data > vle)
				tmp = tmp->lchild;
			else if(tmp->data < vle)
				tmp = tmp->rchild;
			else
				break;
		}
		if(pretmp->lchild == tmp)
			lc = 0;
		else if(pretmp->rchild == tmp)
			lc = 1;
		else//pretmp == tmp,imply the root is the node waited to removed.Because the root node does not input as the formal parameter.
			lc = 2;
		if(tmp->lchild == nullptr || tmp->rchild == nullptr)//it contains the situation:1.BST only have 1 node; 2. 2 node,lchild or rchild.
		{
			if(tmp->lchild == nullptr)//lchild == nullptr or both nullptr.
			{
				if(lc == 0)
					pretmp->lchild = tmp->rchild;
				else if(lc == 1)
					pretmp->rchild = tmp->rchild;
				else//pretmp == tmp,it means the root will be deleted,so need to change it.
					BinTree<T>::root = tmp->rchild;
			}
			else
			{
				if(lc == 0)
					pretmp->lchild = tmp->lchild;
				else if( lc == 1)
					pretmp->rchild = tmp->lchild;
				else
					BinTree<T>::root = tmp->lchild;
			}
		}
		else if(tmp->lchild != nullptr && tmp->rchild != nullptr)
		{

			BinTreeNode<T> *tp;
			tp = tmp->rchild;
			BinTreeNode<T> *rrc = tp;
			BinTreeNode<T> *pretp = tp;
			while(tp->lchild != nullptr)//seek for the first node of rchild of tmp in inorder.
			{
				pretp = tp;
				tp = tp->lchild;
			}
			// if(tp->rchild != nullptr)//if the first node have a rchild.
				pretp->lchild = tp->rchild;
		   /*  else */
				/* pretp->lchild = nullptr; */
			if(lc == 2)
				BinTree<T>::root = tp;
			else if( lc == 1)
				pretmp->rchild = tp;
			else
				pretmp->lchild = tp;
			tp->rchild = rrc;
			tp->lchild = tmp->lchild;
			delete tmp;
			tmp = nullptr;
		}
		return true;
	}
}

	template<typename T>
bool BSTree<T>::Remove(const T &vle,BinTreeNode<T> *&roo)
{
	BinTreeNode<T> *tmp;
	if(roo != nullptr)
	{
		if(roo->data > vle)
			Remove(vle,roo->lchild);
		else if(roo->data < vle)
			Remove(vle,roo->rchild);
		else if(roo->lchild != nullptr && roo->rchild != nullptr)
		{
			tmp = roo->rchild;
			while(tmp->lchild != nullptr)
				tmp = tmp->lchild;
			roo->data = tmp->data;
			Remove(roo->data,roo->rchild);
		}
		else
		{
			tmp = roo;
			if(roo->lchild == nullptr)
				roo = roo->rchild;
			else
				roo = roo->lchild;
			delete tmp;
			tmp = nullptr;
			return true;
		}
	}
	return false;
}

#endif
