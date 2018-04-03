#ifndef _GEN_LIST_H
#define _GEN_LIST_H

#include "sys_comm.h"

template<typename T>
class GenList;

template<typename T>
class GenListNode
{
	public:
		GenListNode():utype(0),tlink(nullptr){info.ref = 0;info.value = 0;info.hlink = nullptr;}
		GenListNode(const GenListNode<T> &p){utype = p.utype;tlink = p.tlink;info = p.info;}
		GenListNode<T>& operator=(const GenListNode<T> &p){utype = p.utype;tlink = p.tlink;info = p.info;}
		
		size_t utype;//utype = 0,头节点;1,数据节点;2,存放指向子表的指针
		GenListNode<T> *tlink;
		struct
		{
			int ref;
			T value;
			GenListNode<T> *hlink;
		}info;
		
};

template<typename T>
class GenList
{
	friend void Createlist(GenListNode<T> *ls,std::istream &is);
	friend void Remove(GenListNode<T> *ls,T x);
	friend bool Equal(GenListNode<T> *l,GenListNode<T> *r);
	friend GenListNode<T> *Next(const GenListNode<T> &elem);
	friend void Traverse(GenListNode<T> *ls);
	public:
		GenList();
		~GenList();
		GenListNode<T> *First();
		bool Copy(const GenList<T> &s);//复制广义表
		size_t Length();
		size_t Depth();
	private:
		GenListNode<T> *first;
		GenListNode<T>* Copy(GenListNode<T> &ls);
	 	void Remove(GenListNode<T> *ls);//被析构函数调用
		size_t length(GenListNode<T> *ls);
		size_t depth(GenListNode<T> *ls);
};

#endif

