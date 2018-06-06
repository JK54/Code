#ifndef _CBTREE_H
#define _CBTREE_H

#include "sys_comm.h"
#include "BinaryTree.hpp"
#include "Stack.hpp"

#define DEFAULTSIZE 100
template<typename T>
class CBTree
{
	public:
		CBTree(int ss = DEFAULTSIZE):Data(new T[ss]),maxsize(ss),size(0){}
		virtual ~CBTree(){delete [] Data;}
		T& operator[](int i){if(i < size)return Data[i];else exit(1);}
		
		int Size(){return size;}
		T Datai(int i){return Data[i];}
		int Maxsize(){return maxsize;}
		bool IsEmpty(){bool e = size > 0?0:1;return e;}
		bool IsFull(){return size == maxsize;}
		void Resize();
		void Insert(const T &vle);
		void Insert(int i,const T &vle);
		void Insert_Noreapting(const T &vle);
		void Clear();
		void BuildTree(std::istream &is);
		void BuildTree(T *,int );
		void TraverseLevelOrder();
		void TraversePostOrder(int i);
		void PrintRelate(int i);
		BinTreeNode<T>* ArrCBT2LinkedBST(int i);
		void LinkedBST2ArrCBT(BinTreeNode<T> *,int);


	protected:
		T *Data;
		int maxsize;
		int size;
};
//---------------Code-----------------------------------------

template<typename T>
void CBTree<T>::Resize()
{
	T *tmpdata = new T[2*maxsize];
	if(tmpdata == nullptr)
	{
		std::cout<<"resize failed.."<<std::endl;
		exit(1);
	}
	for(int i = 0;i< maxsize;i++)
		tmpdata[i] = tmpdata[i];
	delete [] Data;
	Data = tmpdata;
	maxsize *= 2;
}

template<typename T>
void CBTree<T>::Insert(const T &vle)
{
	if(IsFull())
		Resize();
	Data[size++] = vle;
}

template<typename T>
void CBTree<T>::Insert(int i,const T &vle)
{
	if(IsFull())
		Resize();
	if(i < 1 || i > maxsize)
		exit(1);
	Data[i++] = vle;
}
template<typename T>
void CBTree<T>::Insert_Noreapting(const T &vle)
{
	for(int i = 0;i < size;i++)
		if(vle == Data[i])
		{
			std::cout<<vle<<" already exit in the tree.."<<std::endl;
			exit(1);
		}
	Insert(vle);
}

template<typename T>
void CBTree<T>::Clear()
{
	//Considering the type could vary from digit to string,or pointer,so I use "delete" to erase all the data,thought it may be inefficient.
	delete [] Data;
	Data = new T[maxsize];
	size = 0;
}
template<typename T>
void CBTree<T>::BuildTree(std::istream &is)
{
	T tmp;
	while(is>>tmp)
		Insert(tmp);
}

template<typename T>
void CBTree<T>::BuildTree(T *ori,int n)
{
	Clear();
	for(int i = 0;i < n;i++)
		Insert(ori[i]);
}

template<typename T>
void CBTree<T>::TraverseLevelOrder()
{
	if(IsEmpty())
	{
		std::cout<<"empty tree to traverse.."<<std::endl;
		exit(1);
	}
	for(int i = 0;i < size;i++)
	{
		std::cout<<Data[i]<<" ";
		double p = log10(i + 2)/log10(2) - static_cast<int>(log10(i + 2)/log10(2));
		if(p == 0)
			std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

template<typename T>
void CBTree<T>::TraversePostOrder(int i)
{
	if(i >= size)
		return;
	TraversePostOrder(2*i + 1);
	std::cout<<Data[i]<<" ";
	TraversePostOrder(2*i + 2);
}

template<typename T>
void CBTree<T>::PrintRelate(int i)
{
	if(i > maxsize)
	{
		std::cout<<"invalid number"<<std::endl;
		return;
	}
	int p = (i - 1)/2;
	std::cout<<Data[p]<<std::endl;
	TraversePostOrder(2*i + 1);
	TraversePostOrder(2*i + 2);
	std::cout<<std::endl;
}

template<typename T>
BinTreeNode<T>* CBTree<T>::ArrCBT2LinkedBST(int i)
{
	if( i >= size)
		return nullptr;
	BinTreeNode<T> *tmp = new BinTreeNode<T>(Data[i]);
	tmp->lchild = ArrCBT2LinkedBST(2 * i + 1);
	tmp->rchild = ArrCBT2LinkedBST(2 * i + 2);
	return tmp;
}

template<typename T>
void CBTree<T>::LinkedBST2ArrCBT(BinTreeNode<T> *p,int i)
{
	if(p == nullptr)
		return;
	Data[i] = p->data;
	size++;
	if(IsFull())
		Resize();
	LinkedBST2ArrCBT(p->lchild, 2 * i + 1);
	LinkedBST2ArrCBT(p->rchild,2*i + 2);
}
#endif

