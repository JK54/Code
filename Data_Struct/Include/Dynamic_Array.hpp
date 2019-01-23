#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include "sys_comm.h"
#define NODESIZE 10
#define INDEXSIZE 10


//Purpose:try to combine advantages of two classic structures:array and linkedlist.
//Array has good performance in search(time complexity is O(1)),while poor in insert and delete(O(n))
//For linkedlist are O(n) and O(1),use more space to store pointer.
//So that I am trying to think out a structure has O(logn) and O(1).Maybe hashtable is more efficient,but anyway I want to work on it.
//One ArNode has more than half and less than full size elements,split when full and condense when less than half(to make insert and delete more efficient,refer to B-tree).
//Index table record the accumulate num of elements.
//Initial estimate:space complexity is O(n),much more than expexted.
//Question:
//How to optimaze the index table?
template<typename T>
class ArNode
{
	public:
		ArNode(int sz = NODESIZE):data(new T [size]),num(0),size(sz),next(nullptr){}
		ArNode(const T &vle,int sz = NODESIZE)
		{
			data(new T [size]);
			data[0] = vle;
			num = 1;
			size = sz;
			next = nullptr;
		}
		~ArNode(){delete [] data;}
		T& operator[](const int &i){if(i < num) return data[i];else return NULL;}
	public:
		T *data;
		int num;
		int size;
		ArNode *next;
};

template<typename T>
class IndexNode
{
	public:
		IndexNode(const int &num,ArNode<T> *p):count(num),ele(p){}
		int count;
		ArNode<T>* ele;
};

template<typename T>
class Array
{
	public:
		Array();
		~Array();
		bool Insert(const T &vle);
		bool Delete(const T &vle);
		T Search(const T &vle);
		bool Swap(const int &i,const int &j);
		T& operator[](const int &i);
	private:
		IndexNode<T> *index;
		int nodenum;
		int elementnum;
		
		void updateindex();
		void shrink();
		void expand();
};
#endif
