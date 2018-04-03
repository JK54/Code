#ifndef _MATRIX_H
#define _MATRIX_H

#include "sys_comm.h"
#define Default_Size 500

class Matrix_Element
{
	public:
		int x,y,data;
		Matrix_Element *next;
		Matrix_Element(int x = 0,int y = 0,int data = 0):x(x),y(y),data(data),next(nullptr){}
};

class Sparse_Matrix
{
		friend void Swap(Matrix_Element *l,Matrix_Element *r);
	public:
		Sparse_Matrix(int max_x = Default_Size,int max_y = Default_Size):x_size(max_x),y_size(max_y){head = tail = new Matrix_Element;}
		~Sparse_Matrix(){while(head != nullptr){Matrix_Element *tmp = head->next;delete head;head = tmp;}}
		void Mutiply(Sparse_Matrix &,Sparse_Matrix &);
		void Transpose();
		void Traverse();
		void Traverse_Matrix();
		void Build_Matrix(std::istream &is);
		void Sort_X();
		void Sort_Y();
		int X()
		{
			return x_size;
		}
		int Y()
		{
			return y_size;
		}
	private:
		int x_size;
		int y_size;
		Matrix_Element* head;
		Matrix_Element* tail;
};

#endif