#ifndef _BSTree_H
#define _BSTree_H

#include "BinaryTree.hpp"


//the node type is BinTreeNode.
template<typename T>
class BSTree:public BinTree<T>
{
	public:
		BSTree():BinTree<T>(){}
		BSTree(T x):BinTree<T>(x){}
		virtual ~BSTree() = default;

		void CreateTree(std::istream &is);
		void CreateTree(const T a[],int n);
		void CreateTreeByIncSeq(BinTreeNode<T> *&,int low,int high,T a[]);
		void OutPutInOrder(BinTreeNode<T> *roo,T a[]);
		bool Insert(const T &vle);
		bool IsSearchSeq(const T a[],int n);
		bool Remove_NR(const T &vle);
		bool Search(const T &vle);
		bool Remove(const T &vle,BinTreeNode<T> *&roo);//only support for the BSTree,not for AVLTree.
		void RemoveMax();
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
void BSTree<T>::CreateTree(const T a[],int n)
{
	for(int i = 0;i < n;i++)
		Insert(a[i]);
}
template<typename T>
void BSTree<T>::CreateTreeByIncSeq(BinTreeNode<T> *&roo,int low,int high,T a[])
{
	if(low > high)
		roo = nullptr;
	else
	{
		int mid = (low + high)/2;
		if(roo != this->root)
			roo = new BinTreeNode<T>(a[mid - 1]);
		else
			this->root->data = a[mid - 1];
		CreateTreeByIncSeq(roo->lchild,low,mid - 1,a);
		CreateTreeByIncSeq(roo->rchild,mid + 1,high,a);
	}
}

template<typename T>
bool BSTree<T>::Insert(const T &vle)
{
	BinTreeNode<T> *tmp = new BinTreeNode<T>(vle);
	BinTreeNode<T> *roo = BinTree<T>::Root();
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
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *tmp= BinTree<T>::root;
	if(Search(vle) == false)
		return false;
	return true;
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

template<typename T>
void BSTree<T>::OutPutInOrder(BinTreeNode<T> *roo,T a[])
{
	if(roo == nullptr)
	{
		std::cout<<"the tree is empty"<<std::endl;
		return;
	}
	Stack<BinTreeNode<T>*> s;
	int i = 0;
	BinTreeNode<T>* ro = roo;
	while(!s.IsEmpty() || ro != nullptr)
	{
		while(ro != nullptr)
		{
			s.Push(ro);
			ro = ro->lchild;
		}
		if(!s.IsEmpty())
		{
			s.Pop(ro);
			a[i++] = ro->data;
			ro = ro->rchild;
		}
	}
	for(int j = 0;j < i;j++)
		std::cout<<a[j]<<" ";
	std::cout<<std::endl;
}

template<typename T>
void BSTree<T>::RemoveMax()
{
	BinTreeNode<T> *trav = this->root;
	BinTreeNode<T> *pre;
	if(this->root == nullptr)
	{
		std::cout<<"it's an empty tree"<<std::endl;
		exit(1);
	}
	if(this->root->rchild == nullptr)
	{
		std::cout<<"the max element is root,the value is "<<trav->data<<std::endl;
		this->root = this->root->lchild;
		delete trav;
		trav = nullptr;
	}
	else
	{
		while(trav->rchild != nullptr)
		{
			pre = trav;
			trav = trav->rchild;
		}
		std::cout<<trav->data<<"is the max element of tree,deleted"<<std::endl;
		if(trav->lchild == nullptr)
			pre->rchild = nullptr;
		else
			pre->rchild = trav->lchild;
		delete trav;
		trav = nullptr;
	}
}

template<typename T>
bool BSTree<T>::IsSearchSeq(const T a[],int n )
{
	BinTreeNode<T> *trav = this->root;
	for(int i = 0;i < n - 1;i++)
	{
		if(a[i] != trav->data)
			return false;
		if(a[i] > a[i + 1])
			trav = trav->lchild;
		else
			trav = trav->rchild;
	}
	if(trav->data == a[n - 1])
		return true;
	else
		return false;
}
#endif
