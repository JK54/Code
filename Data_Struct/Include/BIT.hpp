#ifndef _BINARY_INDEXED_TREE_H
#define _BINARY_INDEXED_TREE_H

#include "sys_comm.h"
#define DEFAULT_SIZE 100

//definition : squad[i] = raw[i - 2^k + 1] + ... + raw[i],k for LSD of 1.(here the array index i start from 1,not 0;k start from 0)
//e.g:  1 = 001,k = 0,squad[1] = raw[1];
//		2 = 010,k = 1,squad[2] = raw[1] + raw[2];
//		3 = 011,k = 0,squad[3] = raw[3];
//		4 = 100,k = 2,squad[4] = raw[1] + raw[2] + raw[3] + raw[4];
//		5 = 101,k = 0,squad[5] = raw[5];
//		6 = 110,k = 1,squad[6] = raw[5] + raw[6];
//		7 = 111,k = 0,squad[7] = raw[7];
//		8 = 1000,k = 3,squad[8] = raw[1] + ...+ raw[8];
//law:the index which is exactly the power of 2 is the sum from 1 to the index.
//
//for facility,the index 0 store the size of the array.
template<typename T>
class BIT
{
	public:
		BIT(int x = DEFAULT_SIZE);
		~BIT();
		void PrintSize();
		T Sum(int pos);
		void Insert(const T &vle);
		void Modify(int pos,const T &vle);

	private:
		int lowbit(int i){return i & (-i);}//get the Least Significant Digit of 1.
		void resize();
		T *raw;
		T *squad;
		int currentsize;
};

template<typename T>
BIT<T>::BIT(int x)
{
	raw = new T [x];
	squad = new T[x];
	std::memset(raw,0,sizeof(T) * x);
	std::memset(squad,0,sizeof(T) * x);
	raw[0] = x;
	squad[0] = x;
	currentsize = 1;
}

template<typename T>
BIT<T>::~BIT()
{
	delete [] raw;
	delete [] squad;
}

template<typename T>
void BIT<T>::resize()
{
	T *tmpr = new T [2 * raw[0]];
	T *tmps = new T [2 * raw[0]];
	std::memcpy(tmpr,raw,sizeof(T) * raw[0]);
	std::memcpy(tmps,squad,sizeof(T) * raw[0]);
	tmpr[0] = 2 * raw[0];
	tmps[0] = 2 * raw[0];
	delete [] raw;
	delete [] squad;
	raw = tmpr;
	squad = tmps;
}

template<typename T>
void BIT<T>::Modify(int pos,const T &vle)
{
	for(int i = pos;i < currentsize;i += lowbit(i))
		//in case of unsigned 
		squad[i] += vle - raw[pos];
	raw[pos] = vle;
}
template<typename T>
T BIT<T>::Sum(int pos)
{
	T result = 0;
	pos = pos > currentsize ? currentsize - 1 : pos;
	for(int i = pos;i > 0;i -= lowbit(i))
		result += squad[i];
	return result;
}

template<typename T>
void BIT<T>::Insert(const T &vle)
{
	if(currentsize == raw[0])
		resize();
	raw[currentsize] = vle;
	for(int i = currentsize ; i >= currentsize - lowbit(currentsize) + 1;i--)
		squad[currentsize] += raw[i];
	currentsize++;
}


template<typename T>
void BIT<T>::PrintSize()
{
	std::cout<<raw[0]<<std::endl;
	for(int i = 1;i < currentsize;i++)
		std::cout<<raw[i]<<"\t";
	std::cout<<std::endl;
	for(int i = 1;i < currentsize;i++)
		std::cout<<squad[i]<<"\t";
	std::cout<<std::endl;
}

#endif
