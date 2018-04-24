#ifndef _SEQLIST_H
#define _SEQLIST_H

#include "sys_comm.h"
#define DEFAULT_SIZE 100

template <typename T>
class SeqList
{
	public:
		SeqList(int x =DEFAULT_SIZE):capacity(x),size(0),List(new T[x]){}
		~SeqList(){delete [] List;}
		int length() { return size; }
		bool IsEmpty(){if(!size)return true;else return false;}
		void Insert(const T &vle);
		void Resize();
		void Resize(int n);
		void Reserve(int n);
		bool Swap(int i ,int j);
		void Init(std::istream &is);
		void Init(const T a[],int n);
		void Traverse();
		void Reverse();
		void RemoveMin();
		void RemovePos(int i);
		void Remove(const T &vle);
		void RemoveRange(const T &s, const T &t);
		void RemoveRange2(const T &s, const T &t);//ordered
		void RemoveRepeat();
		void InsertPos(int i, const T &vle);
		void Merge(SeqList<T> &L);
		void Min_Max(T &,T&);
		int  Compare(SeqList<T> &L);

	  private:
		int capacity;
		int size;
		T *List;
		void quicksort(int left, int right);
};

template<typename T>
void SeqList<T>::Resize()
{
	T *newL = new T[2*capacity];
	for(int i = 0;i < size;i++)
	{
		newL[i] = List[i];
	}
	delete [] List;
	List = newL;
	capacity *= 2;
}
template<typename T>
void SeqList<T>::Resize(int n)
{
	if(n >capacity)
	{	
		T *newL = new T[n];
		for(int i = 0;i < size;i++)
		{
			newL[i] = List[i];
		}
		delete [] List;
		List = newL;
		capacity = n;
	}
	else
		std::cout<<"n is smaller than current capacity."<<std::endl;
}

template<typename T>
void SeqList<T>::Reserve(int n)
{
	T *tmp = new T[n];
	for(int i = 0;i < n;++i)
		tmp[i] = List[i];
	if(n > size)
	{
		capacity  = n;
	}
	else
	{
		capacity = size = n;
	}
}
template<typename T>
void SeqList<T>::Insert(const T &vle)
{
	if(size < capacity)
	{
		List[size] = vle;
		size++;
	}
	else
	{
		Resize();
		List[size] = vle;
		size++;
	}
}

template<typename T>
bool SeqList<T>::Swap(int i ,int j)//index
{
	if(i <= 0 && j <= 0 && i > size && j >size)
	{
		std::cerr<<"invalid position."<<std::endl;
		return false;
	}
	T tmp;
	tmp = List[i - 1];
	List[i - 1] = List[j - 1];
	List[j  - 1]  = tmp;
	return true;
}
template<typename T>
void SeqList<T>::Init(std::istream &is)
{
	T vle;
	while(is>>vle)
		Insert(vle);
}
template<typename T>
void SeqList<T>::Init(const T *a,int n)
{
	for(int i = 0;i < n;i++)
		Insert(a[i]);
}

template<typename T>
void SeqList<T>::Traverse()
{
	if(IsEmpty())
	{
		std::cerr<<"empty list to traverse.."<<std::endl;
		exit(1);
	}
	for(int i = 0;i < size;++i)
	std::cout<<List[i]<<" ";
	std::cout<<std::endl;
}

template<typename T>
void SeqList<T>::Reverse()
{
	if(IsEmpty())
		exit(1);
	for(int i = 1; i <= size/2;++i)
		Swap(i,size - i + 1);
}

template<typename T>
void SeqList<T>::RemoveMin()
{
	if(IsEmpty())
	{
		std::cout << "Empty List" << std::endl;
		exit(1);
	}
	T tmpmin = List[0];
	int i = 0,pos = 0;
	for (i = 0; i < size; i++)
		if(tmpmin > List[i])
		{
			tmpmin = List[i];
			pos = i;
		}
			List[pos] = List[size - 1];
			size--;
}

template<typename T>
void SeqList<T>::RemovePos(int i)
{
	if( IsEmpty() || i > size)
	{
		std::cout << "invliad pos or empty" << std::endl;
		exit(1);
	}
	for (; i < size;i++)
	{
		List[i - 1] = List[i];
	}
	size--;
}

template<typename T>
void SeqList<T>::InsertPos(int i,const T &vle)
{
	if(size == capacity)
		Resize();
	if (i > size && i < 1)
	{
		std::cout << "invalid pos" << std::endl;
		exit(1);
	}
	for (int j = size; j >= i;--j)
		List[j] = List[j - 1];
	size++;
	List[i - 1] = vle;
}

template<typename T>
void SeqList<T>::Remove(const T &vle)
{
	if(!IsEmpty())
	{
		int i = 0, k = 0;
		for (i = 0; i < size; ++i)
		{
			if(List[i] != vle)
			{
				if(i != k)
					List[k] = List[i];
				k++;
			}
		}
		size = k;
	}
}

template<typename T>
void SeqList<T>::RemoveRange(const T &s,const T &t)
{
	if(!IsEmpty())
	{
		int s0, t0;
		if(s < t)
			s0 = s, t0 = t;
		else
			s0 = t, t0 = s;
		int i = 0, k = 0;
		for (i = 0; i < size; ++i)
		{
			if(List[i] < s0 || List[i] > t0)
				{
				if(i != k)
					List[k] = List[i];
				k++;
				}
		}
		size = k;
	}
}

template<typename T>
void SeqList<T>::quicksort(int left,int right)
{
	if(left < right)
	{
		int pivotpos = left;
		T pivot = List[left - 1];
		for (int i = left + 1; i <= right;++i)
		{
			if(List[i - 1] < pivot)
			{
				pivotpos++;
				if(i != pivotpos)
					Swap(i ,pivotpos);
			}
		}
		Swap(left, pivotpos);
		quicksort(left, pivotpos - 1);
		quicksort(pivotpos + 1, right);
	}
}

template<typename T>
void SeqList<T>::RemoveRange2(const T &s,const T &t)
{
	if(IsEmpty())
	{
		std::cout<<"empty list.."<<std::endl;
		exit(1);
	}
	quicksort(1, size);
	int s0, t0;
	if(s < t)
		s0 = s, t0 = t;
	else
		s0 = t, t0 = s;
	int pos = 1, num = 0;
	int i = 1;
	while (List[i - 1] < s0 && i <= size)
		i++;
	pos = i;
	while (List[i - 1] < t0 && i <= size)
		i++;
	num = i - pos;
	if(pos > size)
	{
		std::cout<<"no elements to remove"<<std::endl;
		exit(1);
	}
	else
	{
		for(int i = pos;i + num <= size;i++)
			List[i - 1] = List[i + num - 1];
		size = size - num;
	}
}

template<typename T>
void SeqList<T>::RemoveRepeat()
{
	if(IsEmpty())
		exit(1);
	int i = 1,k = 1;
	while(i < size)
	{
		if(List[i - 1] != List[i])
		{
			if(i != k)
				List[k] = List[i];
			k++;
		}
		i++;
	}
	size = k;
}
template<typename T>
void SeqList<T>::Merge(SeqList<T> &L)
{
	if(IsEmpty() && L.IsEmpty())
	{
		std::cout<<"two empty list.."<<std::endl;
		exit(1);
	}
	quicksort(1,size);//to make sure the two list is in ordered.
	L.quicksort(1,L.size);
	if(size + L.size >capacity)
		Resize(size + L.size);
	//method 1
   /*  for(int i = size; i < size+ L.size;i++) */
	// {
		// List[i - 1] = L.List[i - size];
	/* } */
	/* quicksort(1,length()); */
	T *tmp = new T[capacity];
	int i = 0,j = 0,k = 0;
	while(i < size && j < L.size)
	{
		if(List[i] <= L.List[j])
			tmp[k++] = List[i++];
		else
			tmp[k++] = L.List[j++];
	}
	while(i < size)
		tmp[k++] = List[i++];
	while(j < L.size)
		tmp[k++] = L.List[j++];
	size = k;
	delete [] List;
	List = nullptr;
	List = tmp;
}

template<typename T>
void SeqList<T>::Min_Max(T &min,T &max)
{
	if(IsEmpty())
		exit(1);
	min = max = List[0];
	for(int i = 0;i < size;++i)
	{
		if(List[i] < min)
			min = List[i];
		else if(List[i] > max)
			max = List[i];
	}
}

template<typename T>
int SeqList<T>::Compare(SeqList<T> &L)
{
	int i = 1;
	while(List[i - 1] == L.List[i - 1] && i <= size && i<= L.size)
		i++;
	if(i >= size && i >= L.size)
	{
		std::cout<<"A equals to B"<<std::endl;
		return 0;
	}
	if(i >= size || List[i- 1] < L.List[i - 1])
	{
		std::cout<<"A is smaller than B"<<std::endl;
		return 1;
	}
	else
	{
		std::cout<<"A is bigger than B"<<std::endl;
		return 2;
	}
	
}
#endif
