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
		~Sparse_Matrix_T() {delete [] smArray;}
		Sparse_Matrix_T<T>& operator=(const Sparse_Matrix_T<T>&);
	
		void Resize();
		void Clear();
		void Init(std::istream &is);
		bool Insert(const int &x,const int &y,const T &vle);
		void Traverse();
		Sparse_Matrix_T<T> Transpose();
		void Transpose(Sparse_Matrix_T<T> &);
		void Add(const Sparse_Matrix_T<T> &);
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
	Terms = p.Terms;
	for(int i = 0;i < p.Terms;i++)
		smArray[i] = p.smArray[i];
	return *this;
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
void Sparse_Matrix_T<T>::Clear()
{
	Rows = Cols = Terms = 0;
}
template<typename T>
void Sparse_Matrix_T<T>::Traverse()
{
	for(int i = 0;i < Terms;i++)
		std::cout<<smArray[i].row<<'\t'<<smArray[i].col<<'\t'<<smArray[i].value<<std::endl;
}

template<typename T>
Sparse_Matrix_T<T>  Sparse_Matrix_T<T>::Transpose()
{
	Sparse_Matrix_T<T> result;
	for(int i = 0;i < Terms;i++)
		result.Insert(smArray[i].col,smArray[i].row,smArray[i].value);
	return result;
}

template<typename T>
void Sparse_Matrix_T<T>::Transpose(Sparse_Matrix_T<T> &result)
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

template<typename T>
void Sparse_Matrix_T<T>::Add(const Sparse_Matrix_T<T> &B)
{
	int i,j,k;
	//ignore the case when A and B have repeating position elements.As a expand,I can also define a function called Similarity() to compare A with B,if the similarity is larger than fifty percent(the larger Terms as the base value of course),then it's unnecessary to Resize().
	while((Terms + B.Terms) > maxsize)	
		Resize();
	//method 1:directly add A and B.If B is unique to A,the worst time complexity is O(n^2 + m),moving every elemets of A behind each time inserting elements of B to A,dissatisfied the require for O(n+m).
	//method 2:moving A to the tail,and then moving to head added with B every time.O(2*n + m) = O(n + m).
	//If the space complexity is not required,I can define another Sparse_Matrix_T to receive the result.it can be O(n+m) as well.In fact it don't have more differences other than using a third array.
	//moving A to the tail.
	for(i = Terms - 1,j = maxsize - 1;i >=0;i--,j--)
		smArray[j] = smArray[i];
	i = maxsize - Terms;
	k = j = 0;
	while(i < maxsize && j < B.Terms)
	{
		if(smArray[i].row < B.smArray[j].row)
			smArray[k++] = smArray[i++];
		else if(smArray[i].row == B.smArray[j].row)
		{
			 if(smArray[i].col == B.smArray[j].col)
			 {
				 smArray[k].row = smArray[i].row;
				 smArray[k].col = smArray[i].col;
				 smArray[k++].value = smArray[i++].value + B.smArray[j++].value;
			 }
			 else if(smArray[i].col < B.smArray[j].col)
			 	smArray[k++] = smArray[i++];
			 else
			 	smArray[k++] = B.smArray[j++];
		}
		else
			smArray[k++] = B.smArray[j++];
	}
	while(i < maxsize)
		smArray[k++] = smArray[i++];
	while(j < B.Terms)
		smArray[k++] = smArray[j++];
	//recount Rows and Cols and clear the tail.It will cause time comlexity increase to O((n+m)^2),but it's necessary,otherwise the Rows and Cols is incorrect.
	Terms = k;
	Rows = Cols = 0;
	// for(j = Terms;i < maxsize;j++)
	for(j = maxsize - 1;j >= Terms;j--)
	{	
		smArray[j].row = 0;
		smArray[j].col = 0;
		smArray[j].value = 0;
	}
	for(i = 0;i < Terms;i++)
	{
		int rc = 0,cc = 0;
		for(j = 0;j < i;j++)
		{
			if(smArray[i].row == smArray[j].row && rc == 0)
				rc = 1;
			if(smArray[i].col == smArray[j].col && cc == 0)
				cc = 1;
		}
		if(rc == 0)
			Rows++;
		if(cc == 0)
			Cols++;
	}
}

template<typename T>
void Sparse_Matrix_T<T>::Multiply(Sparse_Matrix_T<T> &B,Sparse_Matrix_T<T> &Result)
{
	int i,j,k;
	Trituple<T> tmp;
	Sparse_Matrix_T<T> BR;
	//Re-bulid the Result to make sure it is usable for the function.
	while(Rows * B.Cols > Result.maxsize)
		Result.Resize();
	Result.Clear();
	//make the cols of right multuply factor from disordered to ordered.it makes the code concise.
	B.Transpose(BR);
	for(i = 0; i < Terms;++i)	
	{
		for(j = 0; j < B.Terms;++j)
		{
			
		}

	}
}
#endif
