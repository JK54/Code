#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include "LinearList_linked_list.hpp"
#include "Stack.hpp"
template<typename T,typename K>
class HuNode
{
	public:
		HuNode(T vle,K we,HuNode<T,K> *l,HuNode<T,K> *r):data(vle),weight(we),lchild(l),rchild(r){}
		HuNode(T vle,K we):data(vle),weight(we),lchild(nullptr),rchild(nullptr){}
		HuNode():lchild(nullptr),rchild(nullptr){}
		
		T data;
		K weight;
		HuNode<T,K> *lchild;
		HuNode<T,K> *rchild;
};

template<typename T,typename K>
class Huffman
{
	public:
		Huffman():root(nullptr){};
		~Huffman(){destroy(root);}
		void CreateTree(const T a[],const K b[],int n);
		int WPL();
		void TraversePreOrder(HuNode<T,K> *);
		void TraverseInOrder(HuNode<T,K> *);
		void TraversePostOrder(HuNode<T,K> *);
		void Size(HuNode<T,K> *p,int &n);
		HuNode<T,K>* Root(){return root;}
	private:
		HuNode<T,K> *root;
		void destroy(HuNode<T,K> *);
};

template<typename T,typename K>
void Huffman<T,K>::destroy(HuNode<T,K> *p)
{
	if(p == nullptr)
		return;
	destroy(p->lchild);
	destroy(p->rchild);
	delete p;
	p = nullptr;
}

//Hu-Tucker
template<typename T,typename K>
void Huffman<T,K>::CreateTree(const T vle[],const K we[],int n)
{
	HuNode<T,K> *tmp,*tmp1,*tmp2,*min1,*min2;
	int imin1,imin2,num;
	HuNode<T,K> **list = new HuNode<T,K>* [n];
	for(int i = 0;i < n;i++)	
	{
		tmp = new HuNode<T,K>(vle[i],we[i]);
		list[i] = tmp;
	}
	for(num = n;num > 1;num--)
	{
		if(list[0]->weight > list[1]->weight)
		{
			imin1 = 1;
			imin2 = 0;
		}
		else
		{
			imin1 = 0;
			imin2 = 1;
		}
		min1 = list[imin1];
		min2 = list[imin2];
		for(int i = 2;i < num;i++)
		{
			if(list[i]->weight <= min1->weight)
			{
				min2 = list[imin1];
				imin2 = imin1;
				min1 = list[i];
				imin1 = i;
			}
			else if(list[i]->weight > min1->weight && list[i]->weight <= min2->weight)
			{
				min2 = list[i];
				imin2 = i;
			}
		}
		tmp = new HuNode<T,K>(min1->data + min2->data,min1->weight + min2->weight,min1,min2);
		if(imin1 < imin2)
		{
			list[imin1] = tmp;
			for(int i = imin2;i < num - 1;i++)
				list[i] = list[i + 1];
		}
		else
		{
			list[imin2] = tmp;
			for(int i = imin1;i < num - 1;i++)
				list[i] = list[i + 1];
		}
	}
	if(root != nullptr)
		destroy(root);
	root = list[0];
	delete [] list;
}
template<typename T,typename K>
void Huffman<T,K>::TraversePreOrder(HuNode<T,K> *p)
{
	if(p == nullptr)
		return;
	std::cout<<p->data<<" ";
	TraversePreOrder(p->lchild);
	TraversePreOrder(p->rchild);
}
template<typename T,typename K>
void Huffman<T,K>::TraverseInOrder(HuNode<T,K> *p)
{
	if(p == nullptr)
		return;
	TraverseInOrder(p->lchild);
	std::cout<<p->data<<" ";
	TraverseInOrder(p->rchild);
}
template<typename T,typename K>
void Huffman<T,K>::TraversePostOrder(HuNode<T,K> *p)
{
	if(p == nullptr)
		return;
	TraversePostOrder(p->lchild);
	TraversePostOrder(p->rchild);
	std::cout<<p->data<<" ";
}

template<typename T,typename K>
void Huffman<T,K>::Size(HuNode<T,K> *p,int &n)
{
	if(p == nullptr)
		return;
	n++;
	Size(p->lchild,n);
	Size(p->rchild,n);
}

template<typename T,typename K>
int Huffman<T,K>::WPL()
{
	HuNode<T,K> *pre = nullptr,*trav = root;
	int size;
	Size(root,size);
	HuNode<T,K> **path = new HuNode<T,K>* [size];
	int top = -1;
	int wpl = 0;
	while(trav != nullptr)
	{
		path[++top] = trav;
		trav = trav->lchild;
	}
	while(top != -1)
	{
		//gettop
		trav = path[top];
		if(trav->rchild == nullptr || trav->rchild == pre)
		{
			if(trav->lchild == nullptr && trav->rchild == nullptr)
				wpl += trav->weight * top;
			pre = trav;
			top--;
		}
		else
		{
			trav = trav->rchild;
			while(trav != nullptr)
			{
				path[++top] = trav;
				trav = trav->lchild;
			}
		}
	}
	delete [] path;
	return wpl;
}
#endif
