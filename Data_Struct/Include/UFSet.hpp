#ifndef _UFSET_H
#define _UFSET_H

#include "sys_comm.h"
#define MAXSIZE 100
template <typename T>
class UFSet
{
	public:
		UFSet(int max = MAXSIZE):elem(new T[max]),maxsize(max){Init();}
		~UFSet(){delete [] elem;}
		T& operator[](const int &i){if(i >= 0 && i < maxsize)return elem[i];else exit(1);}
		void Init(){std::memset(elem,-1,maxsize*sizeof(T));}
		int FindRoot(int x){while(elem[x] >= 0) x = elem[x];return x;}
		void Merge(int x1,int x2){if(elem[x1] >= 0 || elem[x2] >= 0) return;elem[x1] += elem[x2];elem[x2] = x1;}
		int CollapsePath(int);

	private:
		T *elem;
		int maxsize;
};

//redirect the parent index to the root.
template<typename T>
int UFSet<T>::CollapsePath(int e)
{
	int i,j,r,tmp;
	r = FindRoot(e);
	//collapse all the subbranch of tree r,not only the path of e to r.
	for(i = 0;i < maxsize;i++)
		if(FindRoot(i) == r && elem[i] != r)
		{
			tmp = elem[i];
			elem[i] = r;
			j = i;
			while(elem[tmp] != r)
			{
				j = tmp;
				tmp = elem[tmp];
				elem[j] = r;
			}
		}
	return r;
}
#endif
