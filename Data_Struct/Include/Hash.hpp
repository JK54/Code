#ifndef _HASH_
#define _HASH_

#include "sys_comm.h"

#define DEFAULT_DIV 11
#define DEFAULT_KEYINC 7
#define DEFAULT_SIZE 12

template<typename T>
class HashTable;

template<typename T>
class ChainNode
{
	friend class HashTable<T>;
	T data;
	int keyno;
	ChainNode<T> *next;
	ChainNode(T value = 0):data(value),keyno(key),next(nullptr){key += DEFAULT_KEYINC;}
	static int key;
};

template<typename T>
int ChainNode<T>::key = 0;

template<typename T>
class HashTable
{
	public:
		HashTable(int di = DEFAULT_DIV,int tablesiz = DEFAULT_SIZE):div(di),tablesize(tablesiz),sz(new ChainNode<T>* [di]){}
		~HashTable();
		void Insert(T data);
		void BuildHash(std::istream &is);
		void Traverse();
		bool Remove(int key,T dat);
	private:
		int div;
		int tablesize;
		ChainNode<T> **sz;
};

template<typename T>
HashTable<T>::~HashTable()
{
	if(sz == nullptr)
		return;
	ChainNode<T> *tmp;
	for(int i = 0;i < div; i++)
	{
		tmp = sz[i];
		ChainNode<T> *trav = sz[i];
		while(trav != nullptr)
		{
			tmp = tmp->next;
			delete trav;
			trav = nullptr;
			trav = tmp;
		}
	}
	delete [] *sz;
}

template<typename T>
void HashTable<T>::Insert(T data)
{
	ChainNode<T> *p = new ChainNode<T>(data);
	ChainNode<T> *tmp = sz[p->keyno % div];
	ChainNode<T> *pretmp = tmp;
	while(tmp != nullptr)
	{
		pretmp = tmp;
		tmp = tmp->next;
	}
	if(pretmp != nullptr&& tmp == nullptr)
		pretmp->next = p;
	else
		sz[p->keyno % div] = p;
}

template<typename T>
void HashTable<T>::BuildHash(std::istream &is)
{
	T data;
	while(is>>data)
		Insert(data);
}

template<typename T>
void HashTable<T>::Traverse()
{
	for(int i = 0;i < div; ++i)	
	{
		ChainNode<T> *tmp = sz[i];
		while(tmp != nullptr)
		{
			std::cout<<tmp->data<<" ";
			tmp = tmp->next;
		}
		std::cout<<std::endl;
	}
}

template<typename T>
bool HashTable<T>::Remove(int key,T dat)
{
	int j = key % div;
	ChainNode<T> *tmp = sz[j];
	ChainNode<T> *pretmp = nullptr;
	while(tmp != nullptr && tmp->data != dat)
	{
		pretmp = tmp;
		tmp = tmp->next;
	}
	if(tmp != nullptr)
	{
		if(pretmp == nullptr)
			sz[j] = tmp->next;
		else
			pretmp->next = tmp->next;
		delete tmp;
		tmp = nullptr;
		return true;
	}
	else
		return false;
}
#endif
