#ifndef _BSTree_H
#define _BSTree_H

#include "BinaryTree.hpp"

//the node type is BinTreeNode.
template<typename T>
class BSTree:public BinTree<T>
{
	public:
		BSTree():count(0),BinTree<T>(){}
		explicit BSTree(T x):count(1),BinTree<T>(x){}
		~BSTree(){this->destroy(this->root);}
		
		void CreateTree(std::istream &is);
		void CreateTree(const T a[],int n);
		void CreateTreeByIncSeq(BinTreeNode<T> *&,int low,int high,T a[]);
		void OutPutInOrder(BinTreeNode<T> *roo,T a[]);
		bool Insert(const T &vle);
		bool IsSearchSeq(const T a[],int n);
		bool Search(const T &vle);
		bool Remove(const T &vle,BinTreeNode<T> *&roo);
		bool Remove(const T &vle);
		void RemoveMax();
		void RemoveLessThanX(BinTreeNode<T> *roo,const T &vle);
		void insert(const T&vle){Insert(vle);}
        void erase(const T &vle){Remove(vle);}
        void find(const T &vle){Search(vle);}
		int size(){return count;}
		int Count(){return count;}

	private:
		int count;
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
	BinTreeNode<T> *roo = this->root;
	BinTreeNode<T> *pre = nullptr;
	while(roo != nullptr)
	{
		pre = roo;
		if(roo->data > vle)
			roo = roo->lchild;
		else if(roo->data < vle)
			roo = roo->rchild;
		else
			return false;
	}
	count++;
	roo = new BinTreeNode<T>(vle);
	if(this->root == nullptr)
	{
		this->root = roo;
		return true;
	}
	if(pre->data > vle)
		pre->lchild = roo;
	else
		pre->rchild = roo;
	return true;
}

	template<typename T>
bool BSTree<T>::Search(const T &vle)
{
	BinTreeNode<T> *trav = this->root;
	while(trav != nullptr)
	{
		if(trav->data == vle)
			return true;
		else if(trav->data > vle)
			trav = trav->lchild;
		else 
			trav = trav->rchild;
	}
	return false;
}

template<typename T>
bool BSTree<T>::Remove(const T &vle)
{
	BinTreeNode<T> *pre,*wanted,*trav;
	pre = nullptr;
	wanted = this->root;
	while(wanted != nullptr)
	{
		if(wanted->data == vle)
			break;
		pre = wanted;
		if(wanted->data > vle)
			wanted = wanted->lchild;
		else
			wanted = wanted->rchild;
	}
	if(wanted == nullptr)
		return false;
	count--;
	if(wanted->lchild != nullptr && wanted->rchild != nullptr)
	{
		pre = wanted;
		trav = wanted->lchild;
		while(trav->rchild != nullptr)
		{
			pre = trav;
			trav = trav->rchild;
		}
		wanted->data = trav->data;
		wanted = trav;
	}
	if(wanted->rchild != nullptr)
		trav = wanted->rchild;
	else
		trav = wanted->lchild;
	if(pre != nullptr)
	{
		if(pre->lchild == wanted)
			pre->lchild = trav;
		else
			pre->rchild = trav;
	}
	else
		this->root = trav;
	delete wanted;
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

template<typename T>
void BSTree<T>::RemoveLessThanX(BinTreeNode<T> *roo,const T &vle)
{
	if(roo == nullptr)
		exit(1);
	BinTreeNode<T> *ro;
	BinTreeNode<T> *p = nullptr;
	Queue<BinTreeNode<T>*> q;
	while(roo != nullptr)
	{
		while(roo != nullptr && roo->data <= vle)
		{
			ro = roo;
			roo = roo->rchild;
			ro->rchild = nullptr;
			this->destroy(ro);
			if(p != nullptr)
				p->lchild = roo;
		}
		while(roo != nullptr && roo->data > vle)
		{
			p = roo;
			q.Enqueue(p);
			roo = roo->lchild;
		}
	}
	if(!q.IsEmpty())
		q.Dequeue(this->root);
	else
		this->root = nullptr;
}
#endif
