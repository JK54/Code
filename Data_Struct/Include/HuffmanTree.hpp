#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include "LinearList_linked_list.hpp"

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
		~Huffman(){destory(root);}
		void Hu_Tucker(const T a[],const K b[],int n);
		void Traverse(HuNode<T,K> *);
		HuNode<T,K>* Root(){return root;}
	private:
		HuNode<T,K> *root;
		void destory(HuNode<T,K> *);
};

template<typename T,typename K>
void Huffman<T,K>::destory(HuNode<T,K> *p)
{
	if(p == nullptr)
		return;
	destory(p->lchild);
	destory(p->rchild);
	delete p;
	p = nullptr;
}

template<typename T,typename K>
void Huffman<T,K>::Hu_Tucker(const T vle[],const K we[],int n)
{
	//use a array is also ok,and higher efficient.LinkedList takes more space complexity.
	HuNode<T,K> *tmp,*tmp2;
	//forest list
	LinkedList<HuNode<T,K>*> list;
	LNode<HuNode<T,K>*> *k1,*k2,*t1,*t2;
	for(int i = 0;i < n;i++)	
	{
		tmp = new HuNode<T,K>(vle[i],we[i]);
		list.push_back(tmp);
	}
	while(list.Length() > 1)
	{
		k1 = list.Head();
		k2 = k1->next;
		for(t1 = list.Head(),t2 = k1->next;t2 != nullptr;t1 = t1->next,t2 = t2->next)	
		{
			if(t1->data->weight + t2->data->weight < k1->data->weight + k2->data->weight)
				k1 = t1,k2 = t2;
		}
		list.Delete(k1->data,tmp);
		list.Delete(k2->data,tmp2);
		tmp = new HuNode<T,K>(tmp->data + tmp2->data,tmp->weight + tmp2->weight,tmp,tmp2);
		list.push_back(tmp);
		// list.push_forward(tmp);
	}
	list.pop_forward(root);
}
template<typename T,typename K>
void Huffman<T,K>::Traverse(HuNode<T,K> *p)
{
	if(p == nullptr)
		return;
	Traverse(p->lchild);
	Traverse(p->rchild);
	std::cout<<p->data<<" ";
}
#endif
