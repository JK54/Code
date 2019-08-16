#include <iostream>
#include <cstring>
#include <random>
using std::cin;
using std::cout;
using std::endl;
using std::swap;

template<typename T>
int partition(T data[],int left,int right)
{
	//经过交换，把左，中，右的中间值放到了左边，最小值放到了中间，最大值放到了右边
	int mid = (left + right) / 2;
	int smaller = (data[left] > data[right]) ? right : left;
	if(data[smaller] < data[mid])
		swap(data[smaller],data[mid]);
	if(data[left] > data[right])
		swap(data[left],data[right]);
	int low = left + 1,high = right;
	//双向扫描在近似有序的情况下大幅提升了性能
	//包含low==high的点是为了在所有情况下都能使high点位于low点的左边,且小于基准值
	//可以从两个方向的循环进行分析
	//从左往右，low点要么停留在大于基准值的点，要么越过了high点退出循环。第二种情况下，high点在上一轮循环(如果有）中是因为小于基准值而驻留。
	//从右往左，high点要么停留在小于基准值的点，要么越过了low点退出循环，第二种情况下，low点在上一轮循环因大于基准值而驻留。
	//综上，不论是在内部哪个循环中导致整个循环终止，结果都是high点是最后一个小于基准值的点。
	//当区间长度为2时，三者取中已经进行了排序，只需要进行两次比较与一次运算就结束循环。避免原地交换的比较开销应该小于调用函数的开销。
	while(low <= high)
	{
		while(low <= high && data[low] <= data[left])
			low++;
		while(low <= high && data[left] <= data[high])
			high--;
		if(low < high)
			swap(data[low],data[high]);
	}
	//避免在区间长度为2时原地交换
	if(left != high)
		swap(data[left],data[high]);
	return high;
}

template<typename T>
void quicksort(T data[],int left,int right)
{
	if(left >= right)
		return;
	int pos = partition(data,left,right);
	quicksort(data,left,pos - 1);
	quicksort(data,pos + 1,right);
}

template<typename T>
void disp(T a[],int n)
{
	for(int i = 0;i < n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
template<typename T>
void permutation1(T a[],int start,int end,int &count)
{
	if(a == nullptr)
		return;
	if(start > end)
	{
		cout<<++count<<":";
		for(int i = 0;i <= end;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}
	for(int i = start;i <= end;i++)
	{
		swap(a[start],a[i]);
		permutation1(a,start + 1,end,count);
		swap(a[start],a[i]);
	}
}

template<typename T>
void reverse(T a[],int start,int end)
{
	while(start < end)
	{
		swap(a[start],a[end]);
		start++,end--;
	}
}

template<typename T>
void permutation2(T a[],int endindex)
{
	if(a == nullptr || endindex < 0)
		return;
	quicksort(a,0,endindex);
	int count = 1;
	cout<<count<<":";
	// disp(a,endindex);
	while(1)
	{
		int firstraisepair;
		for(firstraisepair = endindex - 1;firstraisepair >= 0;firstraisepair--)
			if(a[firstraisepair] < a[firstraisepair + 1])
				break;
		if(firstraisepair < 0)
			break;
		for(int i = endindex;i > firstraisepair;i--)
			if(a[i] > a[firstraisepair])
			{
				swap(a[i],a[firstraisepair]);
				break;
			}
		reverse(a,firstraisepair + 1,endindex);
		count++;
		// cout<<count<<":";
		// disp(a,endindex);
	}
	cout<<count<<endl;
}

int main()
{
	char a[] = "abcdfe";
	int b[] = {1,2,23,12,4,3,6};
	int count1 = 0,count2 =0;
	int s1 = strlen(a) - 1;
	int s2 = sizeof(b) / sizeof(b[0]) - 1;
	// permutation1<int>(b,0,s2,count1);
	// permutation1(a,0,s1,count2);
	permutation2(b,s2);
	permutation2(a,s1);
	int c[100];
	std::mt19937 mt(std::random_device{} ());
	for(int i = 0;i < 100;i++)
		c[i] = mt() % 2019;
}
