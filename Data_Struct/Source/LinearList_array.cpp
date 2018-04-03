#include "../Include/LinearList_array.h"

template<typename T>
void LinearList_array<T>::setdata(int i,T &x)
{
	if(!isempty() && i <= maxsize)
	{
		data[i - 1] = x;
	}
	else if(isempty())
	{
		std::cout<<"empty LinearList"<<std::endl;
	}
	else if(!isempty() && i > maxsize)
	{
		std::cout<<"over the linearlist"<<std::endl;
	}
	else
	{
		std::cout<<"other error"<<std::endl;
	}
}

template<typename T>
bool LinearList_array<T>::insert(int i,T &x)
{
	if(!isempty() && i < maxsize)
	{
		for(int j = last; j >= i; --j)
		{
			data[j + 1] = data[j];
		}
		data[i] = x;
		return true;
	}
	else if(!isempty() && i == maxsize)
	{
		resize();
		for(int j = last; j >= i; --j)
		{
			data[j + 1] = data[j];
		}
		data[i] = x;
		return true;

	}
	else if(!isempty() && i > maxsize)
	{
		std::cout<<"over the linearlist"<<std::endl;
		return false;
	}
	else
	{
		std::cout<<"other error"<<std::endl;
		return false;
	}
}

template<typename T>
bool LinearList_array<T>::remove(int i,T &x)
{
	if(!isempty() && i < maxsize)
	{
		x = data[i - 1];
		for(int j = i - 1; j <= last; ++j)
		{
			data[j] = data[j + 1];
		}
		return true;
	}
	else if(!isempty() && i > maxsize)
	{
		std::cout<<"over the linearlist"<<std::endl;
		return false;
	}
	else
	{
		std::cout<<"other error"<<std::endl;
		return false;
	}
}

template<typename T>
bool LinearList_array<T>::isempty() const 
{
	if(maxsize == 0)
	{
		std::cout<<"using isempty().empty linearlist"<<std::endl;
		return true;
	}
	else
		return false;
}

template<typename T>
bool LinearList_array<T>::isfull() const 
{
	if(maxsize - 1== last)
	{
		std::cout<<"using isfull().full linearlist"<<std::endl;
		return true;
	}
	else
		return false;
}

template<typename T>
void LinearList_array<T>::sort() //冒泡法
{
	if(!isempty())
	{
		for(auto i = 0 ; i <= last; ++i)
			for(auto j = i + 1; j <= last; ++j)
			{
				if(data[i] > data[j])
				{
					auto tmp = data[i];
					data[i] = data[j];
					data[j] =  data[i];
				}
			}
	}
	else
		isempty();
}

template<typename T>
void LinearList_array<T>::input()
{
	T tmp;
	std::cout<<"input the value waited to insert"<<std::endl;
	while(std::cin>>tmp)
	{
		if(isempty())
		{
			std::cout<<"using input().the LinearList_array do not new"<<std::endl;
			std::cout<<"input a size to initialize the list"<<std::endl;
			size_t newsize;
			std::cin>>newsize;
			resize(newsize);
		}
		if(isfull())
		{
			resize();
		}
		insert(last,tmp);
		std::cout<<"input the value waited to insert"<<std::endl;
	}	
}

template<typename T>
void LinearList_array<T>::output()
{
	if(isempty())
		exit(1);
	else
	{
		for(int i = 0; i<= last; ++i)
			std::cout<<data[i]<<" "<<std::endl;
	}
}
template<typename T>
void LinearList_array<T>::resize(size_t n)
{
	if(n <= maxsize)
	{
		maxsize = n;
		last =n -1;
	}
	else
	{
		 T *newdata = new T[n];
		 maxsize = n;
		 for(int i = 0 ;i <= last; ++i)
		 {
		 	newdata[i] = data[i];
		 }
		 free();
		 data = newdata;
	}
}

template<typename T>
void LinearList_array<T>::resize()
{
	if(last + 1 == maxsize)
	{
		 T *newdata = new T[2 * maxsize];
		 maxsize = 2 * maxsize;
		 for(int i = 0 ;i <= last; ++i)
		 {
		 	newdata[i] = data[i];
		 }
		 free();
		 data = newdata;
	}
}
#endif
