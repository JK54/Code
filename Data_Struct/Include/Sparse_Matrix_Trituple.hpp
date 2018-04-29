#ifndef _TRITUPLE_MATRIX_H
#define _TRITUPLE_MATRIX_H

#include "sys_comm.h"

#define DEFAULTSIZE 100

template<typename T>
class Sparse_Matrix_T;

template<typename T>
class Trituple
{
	public:
		friend class Sparse_Matrix_T<T>;
		Trituple():row(1),col(1){}
		Trituple(T vle,int x = 1,int y = 1):row(x),col(y),value(vle){}
		Trituple<T>& operator=(const Trituple<T> &p){row = p.row;col = p.col;value = p.value;return *this;}
	private:
		int row;
		int col;
		T value;
};

template<typename T>
class Sparse_Matrix_T
{
	public:
		Sparse_Matrix_T(int maxsize = DEFAULTSIZE):smArray(new Trituple<T>[maxsize]),Rows(0),Cols(0),Terms(0),maxsize(maxsize){}
		~Sparse_Matrix_T() {delete [] smArray; }
		Sparse_Matrix_T<T>& operator=(const Sparse_Matrix_T<T>&);
	
		void Resize();
		void Init(std::istream &is);
		bool Insert(const int &x,const int &y,const T &vle);
		void Traverse();
		void Transpose(Sparse_Matrix_T<T> &);
		void Transpose2(Sparse_Matrix_T<T> &);
		void Multiply(Sparse_Matrix_T<T> &B,Sparse_Matrix_T<T> &Result);

	private:
		Trituple<T> *smArray;
		int Rows,Cols,Terms;
		int maxsize;
};

template<typename T>
Sparse_Matrix_T<T>& Sparse_Matrix_T<T>::operator=(const Sparse_Matrix_T<T> &p)
{
	delete [] smArray;
	smArray = new Trituple<T>[p.maxsize];
	maxsize = p.maxsize;
	Rows = p.Rows;
	Cols = p.Cols;
	for(int i = 0;i < Terms;i++)
		smArray[i] = p.smArray[i];
}
template<typename T>
void Sparse_Matrix_T<T>::Init(std::istream &is)
{
	int x,y;
	T vle;
	while(is>>x>>y>>vle)
		Insert(x,y,vle);
}

template<typename T>
bool Sparse_Matrix_T<T>::Insert(const int &x,const int &y,const T &vle)
{
	int i,j;
	if(Terms == maxsize)
		Resize();
	for(i = 0;smArray[i].row <= x && i < Terms;++i)
	{
		if(smArray[i].row == x &&smArray[i].col == y)
		{
			std::cout<<"the position is occupied.."<<std::endl;
			return false;
		}
		else if(smArray[i].row == x&&smArray[i].col > y)
			break;
	}
	//there are three situation:1.position is occupied;2.x is exited but y is not;3.x and y atr neither existed.
	for(j = Terms; j > i;j--)
		smArray[j] = smArray[j - 1];
	smArray[i].row = x;
	smArray[i].col = y;
	smArray[i].value = vle;
	if(smArray[i - 1].row != x)
		Rows++;
	Cols++;
	Terms++;
	return true;
}

template<typename T>
void Sparse_Matrix_T<T>::Resize()
{
	Trituple<T> *tmp = new Trituple<T>[maxsize*2];
	for(int i = 0;i < maxsize;i++)
		tmp[i] = smArray[i];
	delete [] smArray;
	smArray = tmp;
	maxsize *= 2;
}

template<typename T>
void Sparse_Matrix_T<T>::Traverse()
{
	for(int i = 0;i < Terms;i++)	
		std::cout<<smArray[i].row<<'\t'<<smArray[i].col<<'\t'<<smArray[i].value<<std::endl;
}

template<typename T>
void Sparse_Matrix_T<T>::Transpose(Sparse_Matrix_T<T> &result)
{
	result.maxsize = maxsize;
	delete [] result.smArray;
	result.smArray = new Trituple<T>[maxsize];
	for(int i = 0;i < Terms;i++)
		result.Insert(smArray[i].col,smArray[i].row,smArray[i].value);
}

template<typename T>
void Sparse_Matrix_T<T>::Transpose2(Sparse_Matrix_T<T> &result)
{
	int *rowSize = new int[Cols];
	int *rowStart = new int [Cols];
	int i;
	if(Terms == 0)
	{
		std::cout<<"null maxtrix"<<std::endl;
		exit(1);
	}
	result.Rows = Cols;
	result.Cols = Rows;
	result.Terms = Terms;
	for(i = 0;i<Terms;i++)
		rowSize[smArray[i].col]++;
	rowStart[0] = 0;
	for(i = 1;i<Cols;i++)
		rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
	for(i = 0;i<Terms;i++)
	{
		result.smArray[rowStart[smArray[i].col]++].row = smArray[i].col;
		result.smArray[rowStart[smArray[i].col]++].col = smArray[i].row;
		result.smArray[rowStart[smArray[i].col]++].value = smArray[i].value;
	}
	delete [] rowSize;
	delete [] rowStart;
}
#endif
