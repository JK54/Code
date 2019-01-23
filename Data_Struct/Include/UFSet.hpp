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
		void Merge(int x1,int x2);
		int CollapsePath(int);
		bool IsOne();
		int CountRoot(int *root);
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
		if(i != r && FindRoot(i) == r && elem[i] != r)
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
template <typename T>
void UFSet<T>::Merge(int x1,int x2)
{
	if(x1 == x2)
		return;
	int xp1,xp2;
	xp1 = FindRoot(x1);
	xp2 = FindRoot(x2);
	if(elem[xp1] <= elem[xp2])
	{
		elem[xp1] += elem[xp2];
		elem[xp2] = xp1;
	}
	else
	{
		elem[xp2] += elem[xp1];
		elem[xp1] = xp2;
	}
	CollapsePath(x1);
	CollapsePath(x2);
}
template <typename T>
bool UFSet<T>::IsOne()
{
	int i,j;
	for(i = 0,j = 0;i < maxsize;i++)
		if(elem[i] < 0)
			j++;
	if(j == 1)
		return true;
	else
		return false;
}
template <typename T>
int UFSet<T>::CountRoot(int *root)
{
	int i,j;
	for(i = 0,j = 0;i < maxsize;i++)
		if(elem[i] < 0)
		{
			root[j] = i;
			j++;
		}
	return j;
}
#endif
