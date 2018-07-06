#ifndef _TRITUPLE_MATRIX_H
#define _TRITUPLE_MATRIX_H

#include "sys_comm.h"

#define DEFAULTSIZE 100

template<typename T>
void Swap(T &,T&);

template<typename T>
class Sparse_Matrix_T;

template<typename T>
class Trituple
{
	friend void Swap<int>(int &,int&);
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
	friend void Swap<int>(int &,int&);
	public:
		Sparse_Matrix_T(int maxsize = DEFAULTSIZE):smArray(new Trituple<T>[maxsize]),Rows(0),Cols(0),Terms(0),maxsize(maxsize){}
		~Sparse_Matrix_T() {delete [] smArray;}
		Sparse_Matrix_T<T>& operator=(const Sparse_Matrix_T<T>&);
		Trituple<T>& operator[](int i){return smArray[i];}
	
		void Resize();
		void Clear();
		void Init(std::istream &is);
		bool Insert(const int &x,const int &y,const T &vle);
		void RecountRCT();
		void Traverse();
		Sparse_Matrix_T<T> Transpose();
		void Transpose(Sparse_Matrix_T<T> &);
		void Add(const Sparse_Matrix_T<T> &);
		void Multiply(Sparse_Matrix_T<T> &B,Sparse_Matrix_T<T> &Result);

	private:
		Trituple<T> *smArray;
		int maxsize;
		int Rows,Cols,Terms;//nonzero rows,cols,elements.
		int MaxRow,MaxCol;//the size of matrix,added for compatible usage,major for judging the arithmetic operation is valid or not.
};

template<typename T>
void Swap(T &i,T &j)
{
	T tmp = i;
	i = j;
	j = tmp;
}

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
	int i,j,cc;
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
	//there are three situation:1.position is occupied;2.x is exited but y is not;3.x and y are neither existed.
	for(j = Terms; j > i;j--)
		smArray[j] = smArray[j - 1];
	smArray[i].row = x;
	smArray[i].col = y;
	smArray[i].value = vle;
	//below equal to Recount()
	Terms++;
	if(smArray[i - 1].row != x)
		Rows++;
	cc = 0;
	for(j = 0;j<Terms;j++)
	{
		if(j == i)
			continue;
		if(smArray[j].col == y && cc == 0)
			cc = 1;
	}
	if(cc == 0)
		Cols++;
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
void Sparse_Matrix_T<T>::RecountRCT()
{
	int i,j;
	Rows = Cols = Terms = 0;
	for(i = 0;smArray[i].value != 0;++i)
		Terms++;
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
void Sparse_Matrix_T<T>::Clear()
{
	for(int i = 0;i<Terms;i++)
	{
		smArray[i].row = 0;
		smArray[i].col = 0;
		smArray[i].value = 0;
	}
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
	//a trick of transpose.O(n^2).
	Sparse_Matrix_T<T> result;
	for(int i = 0;i < Terms;i++)
		result.Insert(smArray[i].col,smArray[i].row,smArray[i].value);
	return result;
}

template<typename T>
void Sparse_Matrix_T<T>::Transpose(Sparse_Matrix_T<T> &result)
{
	//The code of the textbook,but the result is incorrect.After thinking and debugging,I found that the problem is the initialization and definition of rowSize array.
	//The Cols of smArray equals to size of rowSize array does not mean the col value of each element equals to the index of rowSize array though it truly have the relations of equality between Cols and size of rowSize.For example,the Cols is 3,while the cols are 1,3,5,only the col "1" can be filled in the rowSize.
	//For completing the code,a extra array is required to record the mapping between index of rowSize and col,but the moving procession is actually a insert sort,no better than shell sort.
	//PS:Use MaxRow,MaxCol here,the auxiliary array.
   //-----------------//
   /*  int *rowSize = new int[Cols]; */
	// int *rowStart = new int [Cols];
	// int *rowMap = new int [Cols];
	// int i,j;
	// if(Terms == 0)
	// {
		// std::cout<<"null maxtrix"<<std::endl;
		// exit(1);
	// }
	// result.Rows = Cols;
	// result.Cols = Rows;
	// result.Terms = Terms;
	// for(i = 0;i<Cols;i++)
		// rowSize[i] = 0;
	// for(i = 0;i<Terms;i++)
		// rowSize[smArray[i].col]++;
	// rowStart[0] = 0;
	// for(i = 1;i<Cols;i++)
		// rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
	// for(i = 0;i<Terms;i++)
	// {
		// j = rowStart[smArray[i].col];
		// result.smArray[j].row = smArray[i].col;
		// result.smArray[j].col = smArray[i].row;
		// result.smArray[j].value = smArray[i].value;
		// rowStart[smArray[i].col]++;
	// }
	// delete [] rowSize;
	// delete [] rowStart;
	/* delete [] rowMap; */
	//--------------------------------------//
	
   /*  //Using shell sort to reorder the smArray in col order */
	result = *this;
	int gap,i,j;
	Trituple<T> tmp;
	gap = Terms;
	while(gap > 1)
	{
		gap = gap/3 + 1;
		for(i = gap;i < Terms;i++)
		{
			if(result.smArray[i - gap].col > result.smArray[i].col)
			{
				tmp = result.smArray[i];
				for(j = i;j >= gap && tmp.col <result.smArray[j - gap].col;j = j - gap)
					result.smArray[j] = result.smArray[j - gap];
				result.smArray[j] = tmp;
			}
		}
	}
	for(i = 0;i < Terms;i++)
		Swap<int>(result.smArray[i].row,result.smArray[i].col);
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
				 if(smArray[i].value + B.smArray[j].value != 0)
				 {
				 	smArray[k].row = smArray[i].row;
				 	smArray[k].col = smArray[i].col;
				 	smArray[k].value = smArray[i].value + B.smArray[j].value;
					++k;
				 }
				 i++,j++;
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
	RecountRCT();
}

template<typename T>
void Sparse_Matrix_T<T>::Multiply(Sparse_Matrix_T<T> &B,Sparse_Matrix_T<T> &result)
{
	int i,j,k;
	Trituple<T> tmp;
	k = 0;
	//Re-bulid the result to make sure it is usable for the function.
	while(Rows * B.Cols > result.maxsize)
		result.Resize();
	result.Clear();
	//Make the cols of right multuply factor B from disordered to ordered can makes the code concise.
	for(i = 0;i < Terms;i++)
	{
		tmp.value = 0;
		for(j = 0;j < B.Terms;j++)
		{
			if(B.smArray[j].row == smArray[i].col)
			{
				tmp.row = smArray[i].row;
				tmp.col = B.smArray[j].col;
				tmp.value = smArray[i].value * B.smArray[j].value;
				int ad = 0;
				for(k = 0;result[k].value != 0;k++)
					if(tmp.row == result[k].row && tmp.col == result[k].col)
					{
						result[k].value += tmp.value;
						ad = 1;
						break;
					}
				if(ad == 0)
				{
					result.Insert(tmp.row,tmp.col,tmp.value);
					result.Terms++;
				}
			}
		}
	}
	//Clear the zero element
	for(k = 0;k < result.Terms;k++)
	{
		if(result[k].value == 0)
		{
			for(j = k;j < result.Terms - 1;j++)
				result[j] = result[j + 1];
		}
	}
	result.RecountRCT();
}
#endif
