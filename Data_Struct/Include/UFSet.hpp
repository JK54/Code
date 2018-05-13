#ifndef _UFSET_H
#define _UFSET_H

#include "sys_comm.h"
#define MAXSIZE 100
template <typename T>
class UFSet
{
	public:
		UFSet(int max = MAXSIZE):elem(new T[max]),maxsize(max),current(0){for(int i = 0;i < maxsize;i++)elem[i] = -1;}
		~UFSet(){delete [] elem;}
		T& operator[](const int &i){if(i >= 0 && i < maxsize)return elem[i];else exit(1);}
		void Init(){for(int i = 0;i < maxsize;i++)elem[i] = -1;}
		int Find(T x){while(elem[x] >= 0) x = elem[x];return x;}
		void Union(T x1,T x2){elem[x2] = x1;elem[x1] += elem[x2];}

	private:
		T *elem;
		int maxsize;
		int current;
};
#endif
