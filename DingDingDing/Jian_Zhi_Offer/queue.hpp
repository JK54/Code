#include <iostream>

#define DEFAULTSIZE 25

template<typename T>
struct Queue
{
	public:
		explicit Queue();
		explicit Queue(const Queue<T> &);
		~Queue();
		T max();
		void push_back(T x);
		void pop_front();
		T front();
		T back();
		int size();
		bool empty();
		Queue& operator=(const Queue<T>&);

	private:
		void expand();
		int datasize,begin,end;
		int maxqueuesize,maxbegin,maxend;
		int capacity,maxcapacity;
		T *data;
		T *maxeleindex;
};

template<typename T>
Queue<T>::Queue()
{
	capacity = maxcapacity = DEFAULTSIZE;
	data = new T [capacity];
	maxeleindex = new T [maxcapacity];
	begin = end = maxbegin = maxend = -1;
	datasize = maxqueuesize = 0;
}

template<typename T>
Queue<T>::~Queue()
{
	delete [] data;
	delete [] maxeleindex;
	datasize = maxqueuesize = capacity = maxcapacity = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T> &ori)
{
	data = new T[ori.capacity];
	maxeleindex = new T[ori.capacity];
	datasize = ori.datasize;
	begin = ori.begin;
	end = ori.end;
	maxbegin = ori.maxbegin;
	maxend = ori.maxend;
	maxqueuesize = ori.maxqueuesize;
	capacity = ori.capacity;
	maxcapacity = ori.maxcapacity;
	if(begin < end)
		for(int i = begin;i < end;i++)
			data[i] = ori.data[i];
	else
	{
		for(int i = 0;i < end;i++)
			data[i] = ori.data[i];
		for(int i = begin;i < capacity;i++)
			data[i] = ori.data[i];
	}

	if(maxbegin < maxend)
		for(int i = maxbegin;i < maxend;i++)
			maxeleindex[i] = ori.maxeleindex[i];
	else
	{
		for(int i = 0;i < maxend;i++)
			maxeleindex[i] = ori.maxeleindex[i];
		for(int i = maxbegin;i < capacity;i++)
			maxeleindex[i] = ori.maxeleindex[i];
	}
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &ori)
{
	delete [] data;
	delete [] maxeleindex;
	data = new T[ori.capacity];
	maxeleindex = new T[ori.capacity];
	datasize = ori.datasize;
	begin = ori.begin;
	end = ori.end;
	maxbegin = ori.maxbegin;
	maxend = ori.maxend;
	maxqueuesize = ori.maxqueuesize;
	capacity = ori.capacity;
	maxcapacity = ori.maxcapacity;
	
	if(begin < end)
		for(int i = begin;i < end;i++)
			data[i] = ori.data[i];
	else
	{
		for(int i = 0;i < end;i++)
			data[i] = ori.data[i];
		for(int i = begin;i < capacity;i++)
			data[i] = ori.data[i];
	}

	if(maxbegin < maxend)
		for(int i = maxbegin;i < maxend;i++)
			maxeleindex[i] = ori.maxeleindex[i];
	else
	{
		for(int i = 0;i < maxend;i++)
			maxeleindex[i] = ori.maxeleindex[i];
		for(int i = maxbegin;i < capacity;i++)
			maxeleindex[i] = ori.maxeleindex[i];
	}
	return *this;
}

template<typename T>
T Queue<T>::max()
{
	return data[maxeleindex[maxbegin]];
}

template<typename T>
T Queue<T>::front()
{
	return data[begin];
}

template<typename T>
T Queue<T>::back()
{
	return data[end];
}

template<typename T>
int Queue<T>::size()
{
	return datasize;
}

template<typename  T>
bool Queue<T>::empty()
{
	if(datasize == 0)
		return true;
	return false;
}

template<typename  T>
void Queue<T>::expand()
{
	T *datatemp = new T [capacity << 1];
	int index = 0,maxindex = 0;
	if(begin < end)
		for(int i = begin;i <= end;i++)
			datatemp[index++] = data[i];
	else
	{
		for(int i = begin;i < capacity;i++)
			datatemp[index++] = data[i];
		for(int i = 0;i <= end;i++)
			datatemp[index++] = data[i];
	}
	begin = 0;
	end = index - 1;
	delete [] data;
	data = datatemp;
	capacity <<= 1;
	
	if(maxqueuesize < (maxcapacity >> 1))
		return;
	T *maxeleindextemp = new T [maxcapacity << 1];
	if(maxbegin < maxend)
		for(int i = maxbegin;i <= maxend;i++)
			maxeleindextemp[maxindex++] = maxeleindex[i];
	else
	{
		for(int i = maxbegin;i < maxcapacity;i++)
			maxeleindextemp[maxindex++] = maxeleindex[i];
		for(int i = 0;i <= maxend;i++)
			maxeleindextemp[maxindex++] = maxeleindex[i];
	}
	maxend = maxindex - 1;
	delete [] maxeleindex;
	maxeleindex = maxeleindextemp;
	maxcapacity <<= 1;
}

template<typename T>
void Queue<T>::push_back(T x)
{
	if(datasize == capacity || maxqueuesize == maxcapacity)
		expand();
	if(end < capacity - 1)
		data[++end] = x;
	else
	{
		end = 0;
		data[end] = x;
	}
	if(begin == -1)
		begin = 0;
	datasize++;

	if(maxbegin <= maxend)
	{
		if(maxbegin != -1)
			for(int i = maxend;i >= maxbegin && x > data[maxeleindex[i]];i--,maxqueuesize--,maxend--);
	}
	else
	{
		int index;
		for(index = maxend;index >= 0 && x > data[maxeleindex[index]];index--,maxqueuesize--,maxend--);
		if(index < 0)
			maxend = capacity - 1;
		for(index = maxend;index >= maxbegin && x > data[maxeleindex[index]];index--,maxqueuesize--,maxend--);
		if(index < maxbegin)
			maxbegin = maxend = -1;
	}

	if(maxend < capacity - 1)
   		maxeleindex[++maxend] = end;
   	else
   	{
   		maxend = 0;
   		maxeleindex[maxend] = end;
   	}
	if(maxbegin == -1)
		maxbegin++;
	maxqueuesize++;
}

template<typename T>
void Queue<T>::pop_front()
{
	if(maxeleindex[maxbegin] == begin)
	{
		if(maxqueuesize == 1)
			maxbegin = maxend = -1;
		else
		{
			if(maxbegin == maxcapacity - 1)
				maxbegin = 0;
			else
				maxbegin++;
		}
		maxqueuesize--;
	}
	if(datasize == 1)
		begin = end = -1;
	else if(begin == capacity - 1)
		begin = 0;
	else
		begin++;
	datasize--;
}
