#ifndef _MATRIX_H
#define _MATRIX_H

#include "sys_comm.h"
#define Default_Size 5000

template<typename T>
class Matrix_Element
{
	public:
		int x,y;
		T data;
		Matrix_Element<T> *next;
		Matrix_Element(int x = 0,int y = 0,T data = 0):x(x),y(y),data(data),next(nullptr){}
};

template<typename T>
class Sparse_Matrix
{
		friend void Swap(Matrix_Element<T> *l,Matrix_Element<T> *r);
	public:
		Sparse_Matrix(int max_x = Default_Size,int max_y = Default_Size):x_size(max_x),y_size(max_y){head = tail = new Matrix_Element<T>;}
		~Sparse_Matrix(){while(head != nullptr){Matrix_Element<T> *tmp = head->next;delete head;head = tmp;}}
		void Mutiply(Sparse_Matrix<T> &,Sparse_Matrix<T> &);
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
		Matrix_Element<T> *head;
		Matrix_Element<T> *tail;
};


template<typename T>
void Sparse_Matrix<T>::Build_Matrix(std::istream &is)
{
	int x,y;
	T data;
	while(is>>x>>y>>data)
	{
		if(x < x_size && y < y_size)
		{
			Matrix_Element<T> *tmp = new Matrix_Element<T>(x,y,data);
			tail->next = tmp;
			tail = tail->next;
		}
	}
	
}

template<typename T>
void Swap(Matrix_Element<T> *l,Matrix_Element<T> *r)
{
	int x0 = l->x;
	int y0 = l->y;
	T data0 = l->data;
	l->x = r->x;
	l->y = r->y;
	l->data = r->data;
	r->x = x0;
	r->y = y0;
	r->data =data0;
}

template<typename T>
void Sparse_Matrix<T>::Sort_X()
{
	if(head == nullptr)
		return;
	for(Matrix_Element<T> *p = head->next;p->next != nullptr;p = p->next)
	{
		for(Matrix_Element<T> *q = p;q->next != nullptr; q = q->next)
		{
			if(q->x > q->next->x)
				Swap(q,q->next);
			else if(q->x == q->next->x)
				if(q->y > q->next->y)
					Swap(q,q->next);
		}
	}
}

template<typename T>
void Sparse_Matrix<T>::Sort_Y()
{
	if(head == nullptr)
		return;
	for(Matrix_Element<T> *p = head->next;p->next != nullptr;p = p->next)
	{
		for(Matrix_Element<T> *q = p;q->next != nullptr; q = q->next)
		{
			if(q->y > q->next->y)
				Swap(q,q->next);
			else if(q->y == q->next->y)
				if(q->x > q->next->x)
					Swap(q,q->next);
		}
	}
}

template<typename T>
void Sparse_Matrix<T>::Traverse()
{
	if(head == nullptr)
		return;
	Matrix_Element<T> *p = head->next;
	while(p!= nullptr)
	{	
		std::cout<<p->x<<" "<<p->y<<" "<<p->data<<std::endl;	
		p = p->next;
	}
	std::cout<<std::endl;
}

template<typename T>
void Sparse_Matrix<T>::Traverse_Matrix()
{
	Matrix_Element<T> *p = head->next;
	std::vector<std::vector<int>> A(x_size,std::vector<int>(y_size,0));
	// A.resize(x_size,y_size);
	while(p != nullptr)
	{
		A[p->x - 1][p->y - 1] = p->data;
		p = p->next;
	}
	for(int i = 0; i < y_size; ++i)
	{
		for(int j = 0; j < x_size; ++j)
		{
			std::cout<<A[j][i]<<" ";
		}
		std::cout<<std::endl;
	}
}

template<typename T>
void Sparse_Matrix<T>::Transpose()
{
	Matrix_Element<T> *p = head->next;
	while(p != nullptr)
	{
		int tmp;
		tmp = p->x;
		p->x = p->y;
		p->y = tmp;
		p = p->next;
	}
}

template<typename T>
void  Sparse_Matrix<T>::Mutiply(Sparse_Matrix<T> &x,Sparse_Matrix<T> &result)
{
	assert(y_size == x.x_size);
	// Sort_Y();
	// x.Sort_X();
	for (Matrix_Element<T> *p = head->next; p != nullptr; p = p->next)
	{
		for(Matrix_Element<T> *q = x.head->next; q != nullptr; q = q->next)
		{
			if(p->x == q->y)
			{
				Matrix_Element<T> *trav = result.head->next;
				while(trav != nullptr && (trav->x != q->x || trav->y != p->y))
					trav = trav->next;
				if(trav == nullptr)
				{
					result.tail->next = new Matrix_Element<T>;
					result.tail = result.tail->next;
					trav = result.tail;
					trav->x = q->x;
					trav->y = p->y;
				}
				trav->data += p->data * q->data;
			}
		}
	}
}

#endif
