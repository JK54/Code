#include "Sparse_Matrix.h"

void Sparse_Matrix::Build_Matrix(std::istream &is)
{
	int x,y,data;
	while(is>>x>>y>>data)
	{
		if(x < x_size && y < y_size)
		{
			Matrix_Element *tmp = new Matrix_Element(x,y,data);
			tail->next = tmp;
			tail = tail->next;
		}
	}
	
}

void Swap(Matrix_Element *l,Matrix_Element *r)
{
	int x0 = l->x;
	int y0 = l->y;
	int data0 = l->data;
	l->x = r->x;
	l->y = r->y;
	l->data = r->data;
	r->x = x0;
	r->y = y0;
	r->data =data0;
}
void Sparse_Matrix::Sort_X()
{
	if(head == nullptr)
		return;
	for(Matrix_Element *p = head->next;p->next != nullptr;p = p->next)
	{
		for(Matrix_Element *q = p;q->next != nullptr; q = q->next)
		{
			if(q->x > q->next->x)
				Swap(q,q->next);
			else if(q->x == q->next->x)
				if(q->y > q->next->y)
					Swap(q,q->next);
		}
	}
}
void Sparse_Matrix::Sort_Y()
{
	if(head == nullptr)
		return;
	for(Matrix_Element *p = head->next;p->next != nullptr;p = p->next)
	{
		for(Matrix_Element *q = p;q->next != nullptr; q = q->next)
		{
			if(q->y > q->next->y)
				Swap(q,q->next);
			else if(q->y == q->next->y)
				if(q->x > q->next->x)
					Swap(q,q->next);
		}
	}
}

void Sparse_Matrix::Traverse()
{
	if(head == nullptr)
		return;
	Matrix_Element *p = head->next;
	while(p!= nullptr)
	{	
		std::cout<<p->x<<" "<<p->y<<" "<<p->data<<std::endl;	
		p = p->next;
	}
	std::cout<<std::endl;
}

void Sparse_Matrix::Traverse_Matrix()
{
	Matrix_Element *p = head->next;
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

void Sparse_Matrix::Transpose()
{
	Matrix_Element *p = head->next;
	while(p != nullptr)
	{
		int tmp;
		tmp = p->x;
		p->x = p->y;
		p->y = tmp;
		p = p->next;
	}
}

void  Sparse_Matrix::Mutiply(Sparse_Matrix &x,Sparse_Matrix &result)
{
	assert(y_size == x.x_size);
	Sort_Y();
	x.Sort_X();
	for (Matrix_Element *p = head->next; p != nullptr; p = p->next)
	{
		for(Matrix_Element *q = x.head->next; q != nullptr; q = q->next)
		{
			if(p->x == q->y)
			{
				Matrix_Element *trav = result.head->next;
				while(trav != nullptr && (trav->x != q->x || trav->y != p->y))
					trav = trav->next;
				if(trav == nullptr)
				{
					result.tail->next = new Matrix_Element;
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
