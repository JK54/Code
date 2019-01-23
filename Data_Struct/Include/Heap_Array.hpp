#ifndef _HEAP_ARR
#define _HEAP_ARR

#include "CompleteBinaryTree.hpp"
//heap protected member are size and maxsize,ref from the include file.
template<typename T>
class Heap:public CBTree<T>
{
	public:
		Heap(int sz = DEFAULTSIZE):CBTree<T>(sz){}
		void CreateHeap(const T arr[], int n);
		void CreateHeap(std::istream &is);
		bool Insert(const T &vle);
		bool Remove(T &vle);
		virtual void siftUp(int i,int m) = 0;
		virtual void siftDown(int i,int m) = 0;
		virtual bool IsHeap() = 0;
};


template<typename T>
class MinHeap : public Heap<T>
{
	public:
		MinHeap(int sz = DEFAULTSIZE):Heap<T>(sz){}
		virtual void siftUp(int i,int m) override;
		virtual void siftDown(int i,int m) override;
		virtual bool IsHeap() override;
};
template<typename T>
class MaxHeap : public Heap<T>
{
	public:
		MaxHeap(int sz = DEFAULTSIZE):Heap<T>(sz){}
		virtual void siftUp(int i,int m) override;
		virtual void siftDown(int i,int m) override;
		virtual bool IsHeap() override;
};

template<typename T>
void Heap<T>::CreateHeap(const T arr[],int n)
{
	for(int i = 0;i < n;i++)
		Insert(arr[i]);
}

template<typename T>
void Heap<T>::CreateHeap(std::istream &is)
{
	T vle;
	while(is >> vle)
		Insert(vle);
}
template<typename T>
bool Heap<T>::Insert(const T &vle)
{
	if(this->IsFull())
		CBTree<T>::Resize();
	this->size++;
	this->Data[this->size - 1] = vle;
	siftUp(this->size - 1,0);
	return true;

}
template<typename T>
bool Heap<T>::Remove(T &vle)
{
	if(this->size == 0)	
		return false;
	vle = this->Data[0];
	this->Data[0] = this->Data[this->size - 1];
	this->size--;
	siftDown(0,this->size - 1);
	return true;
}
template<typename T>
void MinHeap<T>::siftUp(int i ,int m)
{
	//from bottom i to top m
	int j = i;
	int p = (j - 1)/2;
	T tmp = this->Data[j];
	while(j > m)
	{
		if(this->Data[p] <= tmp)
			break;
		else
		{
			this->Data[j] = this->Data[p];
			j = p;
			p =(p - 1)/2;
		}
	}
	this->Data[j] = tmp;
}

template<typename T>
void MinHeap<T>::siftDown(int i,int m)
{
	//from top i tp bottom m
	int trav = i;
	int ctrav = 2*trav + 1;
	T tmp = this->Data[trav];
	while(ctrav <= m)
	{
		if(ctrav < m && this->Data[ctrav] > this->Data[ctrav + 1])
			ctrav++;
		if(this->Data[ctrav] > tmp)
			break;
		else
		{
			this->Data[trav] = this->Data[ctrav];
			trav = ctrav;
			ctrav = ctrav * 2 + 1;
		}
	}
	this->Data[trav] = tmp;
}

template<typename T>
bool MinHeap<T>::IsHeap()
{
	int n = this->size;
	if(n % 2 == 0)
	{
		if(this->Data[n / 2 - 1] < this->Data[n - 1])
		{
			std::cout<<"Not Heap1!"<<std::endl;
			return false;	
		}
		for(int i = 0;i < n / 2;i++)
		{
			if(this->Data[i] < this->Data[2 * i + 1] || this->Data[i] < this->Data[2 * i + 2])
			{
				std::cout<<"Not Heap2!"<<std::endl;
				return false;
			}
		}
	}
	else
	{
		for(int i = 0;i < n / 2;i++)
		{
			if(this->Data[i] > this->Data[2 * i + 1] || this->Data[i] > this->Data[2 * i + 2])
			{
				std::cout<<"Not Heap!"<<std::endl;
				return false;
			}
		}
	}
	std::cout<<"Heap!"<<std::endl;
	return true;
}

template<typename T>
void MaxHeap<T>::siftUp(int i ,int m)
{
	//from bottom i to top m
	int j = i;
	int p = (j - 1)/2;
	T tmp = this->Data[j];
	while(j > m)
	{
		if(this->Data[p] > tmp)
			break;
		else
		{
			this->Data[j] = this->Data[p];
			j = p;
			p =(p - 1)/2;
		}
	}
	this->Data[j] = tmp;
}
template<typename T>
void MaxHeap<T>::siftDown(int i,int m)
{
	int trav = i;
	int ctrav = 2*trav + 1;
	T tmp = this->Data[trav];
	while(ctrav <= m)
	{
		if(ctrav < m && this->Data[ctrav] < this->Data[ctrav + 1])
			ctrav++;
		if(this->Data[ctrav] < tmp)
			break;
		else
		{
			this->Data[trav] = this->Data[ctrav];
			trav = ctrav;
			ctrav = ctrav * 2 + 1;
		}
	}
	this->Data[trav] = tmp;
}
template<typename T>
bool MaxHeap<T>::IsHeap()
{
	int n = this->size;
	if(n % 2 == 0)
	{
		if(this->Data[n / 2 - 1] < this->Data[n - 1])
		{
			std::cout<<"Not Heap1!"<<std::endl;
			return false;	
		}
		for(int i = 0;i < n / 2;i++)
		{
			if(this->Data[i] < this->Data[2 * i + 1] || this->Data[i] < this->Data[2 * i + 2])
			{
				std::cout<<"Not Heap2!"<<std::endl;
				return false;
			}
		}
	}
	else
	{
		for(int i = 0;i < n / 2;i++)
		{
			if(this->Data[i] < this->Data[2 * i + 1] || this->Data[i] < this->Data[2 * i + 2])
			{
				std::cout<<"Not Heap3!"<<std::endl;
				return false;
			}
		}
	}
	std::cout<<"Heap!"<<std::endl;
	return true;
}

#endif
