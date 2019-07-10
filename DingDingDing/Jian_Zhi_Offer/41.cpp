#include <vector>
#include <iostream>
#include <algorithm>
#include "maxheap.h"
#include "minheap.h"
#include "quicksort.cpp"
#include <random>
using std::vector;
using std::cin;
using std::cout;
using std::endl;

template<typename T>
class d4mid
{
	private:
		vector<T> max;
		vector<T> min;
	public:
		T mid()
		{
			int size = max.size() + min.size();
			if(size == 0)
				throw "empty array";
			if(size & 1)
				return max[0];
			else
				return (min[0] + max[0]) >> 1;
		}
		//当前数据个数为偶数次插入max，奇数次插入min。
		void insert(T num)
		{
			int size = max.size() + min.size();
			if(size & 1)
			{
				if(min.size() > 0 && num < max[0])
				{
					max.push_back(num);
					push_heap(max.begin(),max.end(),std::less<T>());
					num = max[0];
					pop_heap(max.begin(),max.end(),std::less<T>());
					max.pop_back();
				}
				min.push_back(num);
				push_heap(min.begin(),min.end(),std::greater<T>());
			}
			else
			{
				if(size > 0 && min[0] < num)
				{
					min.push_back(num);
					push_heap(min.begin(),min.end(),std::greater<T>());

					num = min[0];
					pop_heap(min.begin(),min.end(),std::greater<T>());
					min.pop_back();
				}
				max.push_back(num);
				push_heap(max.begin(),max.end(),std::less<T>());
			}
		}
};

struct d4mid2
{
	MaxHeap max;
	MinHeap min;

	int mid()
	{
		int size = max.size + min.size;
		if(size == 0)
			throw "dididi";
		if(size & 1)
			return max.top();
		else
			return (max.top() + min.top()) >> 1;
	}

	void insert(int num)
	{
		int size = max.size + min.size;
		int tmp;
		if(size & 1)
		{
			if(min.size > 0 && num < max.top())
			{
				max.push(num);
				num = max.top();
				max.pop();
			}
			min.push(num);
		}
		else
		{
			if(max.size > 0 && num > min.top())
			{
				min.push(num);
				num = min.top();
				min.pop();
			}
			max.push(num);
		}
	}
};

int main()
{
	int n;
	cin>>n;
	int *a = new int[n];
	d4mid2 aaa;
	std::random_device rd;
	std::mt19937 mt(rd());
	
	for(int i = 0;i < n;i++)
	{
		a[i] = mt() % 1000000;
		aaa.insert(a[i]);
	}
	quicksort<int>(a,0,n - 1);

	for(int i = 0;i < n;i++)
		cout<<a[i]<<" ";
	cout<<endl<<endl;
	
	cout<<aaa.mid()<<endl;
	if(n&1)
		cout<<a[n/2]<<endl;
	else
		cout<<(a[n/2] + a[n/2 - 1]) / 2<<endl;
	delete [] a;
}
