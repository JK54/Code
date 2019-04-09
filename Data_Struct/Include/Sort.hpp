#ifndef _SORT_H
#define _SORT_H

#include "sys_comm.h"
#include "Heap_Array.hpp"
#include "CompleteBinaryTree.hpp"
#include "LinearList_linkedlist.hpp"
#include "LinearList_seqlist.hpp"
#include "Queue.hpp"
#define I_MAX 65535
#define DEFAULT_SIZE 100//default maxsize of DataList
#define THRESH_Q_I 5//threshold of quicksort,when the length is less than threshold,use insertsort instand,the value between 5 to 25 is suitable.

template<typename T>
class Element
{
	public:
		//we can also define more key or data member,blank for default.
		Element(){}
		Element(T x):key(x){}
		T key;
		Element<T>& operator=(const Element<T> &x){key = x.key;return *this;}
		bool operator==(const Element<T> &x){return key == x.key;}
		bool operator!=(const Element<T> &x){return key != x.key;}
		bool operator!=(const T &x){return key !=x;}
		bool operator<=(const Element<T> &x){return key <= x.key;}
		bool operator>=(const Element<T> &x){return key >= x.key;}
		bool operator<(const Element<T> &x) {return key < x.key;}
		bool operator>(const Element<T> &x) {return key > x.key;}
		bool operator>(T &x) {return key > x;}
		bool operator<(T &x) {return key < x;}
		// T& operator/(T &x){return key / x;}
	friend std::ostream& operator<<(std::ostream &os,const Element<T> &x){os<<x.key<<" ";return os;}
};

template<typename T>
class DataList
{
	public:
		DataList(int s = DEFAULT_SIZE):Data(new Element<T>[s]),maxsize(s),currentsize(0){}
		DataList(T mv,int s = DEFAULT_SIZE):Data(new Element<T>[s]),maxvalue(mv),maxsize(s),currentsize(0){}
		~DataList(){delete [] Data;}
		Element<T>& operator[](int i){return Data[i];}
		void SetMaxvalue(T x){maxvalue = x;}
		void Initial(std::istream &is);
		void Initial(T a[],int n);
		void Insert(const T &vle);
		void swap(Element<T> &p,Element<T> &q);
		int Length(){return currentsize;}
		bool IsEmpty();
		bool IsSorted(T *,int );
		void Traverse();

		//insert sort
		//best for basic ordered sequence.
		void InsertSort();
		void BinaryInsertSort();
		void ShellSort();		
		
		//swap sort
			//bubble sort
		void BubbleSort();
		void BubbleSort_I();
		void CocktailSort();
			//quick sort
		int Partition_Left(const int &left,const int &right);
		int Partition_Random(const int &left,const int &right);
		int Partition_Medium3(DataList<T> &L,const int &left,const int &right);
		void Partition_Repeat(DataList<T> &,const int &left,const int &right,int &lborder,int &rborder);
			//no-recursion
		void QuickSort();
			//recursion
		void QuickSort(DataList<T> &L,const int &left,const int &right);//basical quick sort.
		void Quick_Insert_Mixed_Sort(DataList<T> &L,const int &left,const int &right);//mixed sort.
			//efficient quick sort mixed with insert sort.
		void Quick_Sort_Part(DataList<T> &L,const int &left,const int &right);
		void HybirdSort(DataList<T> &L,const int &left,const int &right);	
		
		//select sort
		void SelectSort();
		void MinHeapSort();
		void MaxHeapSort();
		void TournamentSort();
		void SCountingSort();
		//merge sort
		void MergeSort(const int &left,const int &right);
		void MergeSort();
		//here designate mid,because there are the situation:the array is odd,that the last element is very hard to handle,if using mid parameter it could be easy to merge unequal length array.if it's odd,handle the right half elements before the final merge.
		void Merge(const int &left,const int &mid,const int &right);

		void LSD(const int &bit,const int &scale){lsd(bit,scale);}
		void LSD(const int &scale);
		void MSD(const int &bit,const int &scale);
		void MSD(const int &scale);
		void BucketSort();
		void CountingSort();
		//Search
		int DivKSearch(const T &x,const int &k);

		//Application
		Element<T> FindK(const int &left,const int &right,const int &k);
	private:
		Element<T> *Data;
		T maxvalue;
		int maxsize;
		int currentsize;

		void swap(T &a,T &b);
		void siftupmax(const int &,const int &);
		void siftdownmax(const int &,const int &);
		void siftupmin(const int &,const int &);
		void siftdownmin(const int &,const int &);
		void lsd(const int &bit,const int &scale);
		void msd(Queue<Element<T>> &q,const int &bit,const int &scale);
};


template<typename T>
void DataList<T>::Initial(std::istream &is)
{
	int i = currentsize;
	T vle;
	while(is>>vle)
	{
		Insert(vle);
		i++;
	}
}

template<typename T>		
void DataList<T>::Initial(T a[],int n)
{
	int j = 0;
	while(j < n)
		Insert(a[j++]);
}

template<typename T>
void DataList<T>::Insert(const T &vle)
{
	if(currentsize == maxsize)
	{
		maxsize *= 2;
		Element<T> *tmp = new Element<T>[maxsize];
		std::copy(&Data[0],&Data[maxsize - 1],tmp);
		delete [] Data;
		Data = tmp;
	}
	Data[currentsize].key = vle;
	currentsize++;
}

template<typename T>
void DataList<T>::swap(T &p,T &q)
{
	T tmp = p;
	p = q;
	q = tmp;
}

template<typename T>
void DataList<T>::swap(Element<T> &p,Element<T> &q)
{
	Element<T> tmp = p;
	p = q;
	q = tmp;
}

template<typename T>
bool DataList<T>::IsEmpty()
{
	if(!currentsize)
	{
		std::cout<<"empty.."<<std::endl;
		return true;
	}
	else 
		return false;
}

//a is a origin source array of Data.
template<typename T>
bool DataList<T>::IsSorted(T a[],int n)
{
	if(n != currentsize)
		return false;
	T *tmp = new T [n];
	int count = 0;
	int diff;
	for(diff = 1;diff < currentsize;diff++)
		if(Data[diff] != Data[diff - 1])
			break;
	//copy elements to tmp array and check if sorted(ascend or descend))
	if(Data[0] < Data[diff])
	{
		for(int i = 1;i < n;i++)
		{
			tmp[i - 1] = Data[i - 1].key;
			if(Data[i - 1] > Data[i])
			{
				std::cout<<"DisOrdered"<<std::endl;
				return false;
			}
		}
	}
	else
	{
		for(int i = 1;i < n;i++)
		{
			tmp[i - 1] = Data[i - 1].key;
			if(Data[i - 1] < Data[i])
			{
				std::cout<<"DisOrdered"<<std::endl;
				return false;
			}
		}	
	}
	tmp[n - 1] = Data[n - 1].key;
	//check if elements losr after sort(for unstable sort)
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n - count;j++)
		{
			if(a[i] == tmp[j])
			{
				for(int k = j;k < n - count - 1;k++)
					tmp[k] = tmp[k + 1];
				count++;
				break;
			}
			else
			{
				if(Data[0] > Data[diff])
				{
					if((j == 0 && a[i] > tmp[j]) || (j == n - count - 1 && a[i] < tmp[j]) || (a[i] > tmp[j] && a[i] < tmp [j - 1]))
					{
						std::cout<<"Lost Element"<<std::endl;
						return false;
					}
				}
				else
				{
					if((j == 0 && a[i] < tmp[j]) || (j == n - count - 1 && a[i] > tmp[j]) || (a[i] < tmp[j] && a[i] > tmp [j - 1]))
						{
							std::cout<<"Lost Element"<<std::endl;
							return false;
						}
				}
			}
		}
	}
	delete [] tmp;
	if(Data[0] > Data[diff])
		std::cout<<"Descending Order"<<std::endl;
	else
		std::cout<<"Ascending Order"<<std::endl;
	return true;
}

template<typename T>
void DataList<T>::Traverse()
{
	for(int i = 0;i<currentsize;++i)
		std::cout<<Data[i]<<" ";
	std::cout<<std::endl;
}

//main idea:
//1).Check if the incoming element is bigger than previous or not.If bigger,come to next elem,else go to 2)
//2).Record key value of the incoming,compare with the previous sequence to find the positon to insert,make sure that it smaller than follwing and bigger than previous.Move the elements behind in the process of comparing,to create space for the new element.

//assessment:
//1)Stable.
//2)Space complexity is S(1).
//3)Time Complexity:best(already ordered,comparing one time in each round),worst(comparing until the first position in every round.)
//			O(compare)		O(Move)
//best			n			   1
//avg		  n^2/4			 n^2/4
//worst		Σ(n,i=2)i		Σ(n,i=2)(i+1)
//
template<typename T>
void DataList<T>::InsertSort()
{
	if(IsEmpty())
		return;
	Element<T> tmp;
	int j;
	for(int i = 1;i < currentsize;++i)
	{
		if(Data[i - 1] > Data[i])
		{
			tmp = Data[i];
			j = i;
			while(j >= 1 && tmp < Data[j - 1])
			{
				Data[j] = Data[j - 1];
				--j;
			}
			Data[j] = tmp;
		}
	}
}

//main idea:
//Similarly to InsertSort,the differece is that BinaryInsertSort find the inserted position by bisearch.
//
//assessment:
//1)Stable.
//2)Space complexity is S(1).
//3)Time Complexity:
template<typename T>
void DataList<T>::BinaryInsertSort()
{
	if(IsEmpty())
		return;
	Element<T> tmp;
	int low,high,middle;
	for(int i = 1; i < currentsize; ++i)
	{
		if(Data[i - 1] > Data[i])
		{
			tmp = Data[i];
			low = 0;
			high = i - 1;
			while(low <= high)
			{
				middle = (low + high)/2;
				if(tmp < Data[middle])
					high = middle - 1;
				else
					low = middle + 1;
			}
			for(int j = i - 1 ; j >= low; j--)
				Data[j + 1] = Data[j];
			Data[low] = tmp;
		}
	}
}

//main idea:
//Slice sequence serveral times by a decreasing gap from size/3 + 1 to 1.the others is the same as InsertSort.
//Unstable
template<typename T>
void DataList<T>::ShellSort()
{
	int i,j,gap = currentsize;
	Element<T> tmp;
	while(gap > 1)
	{
		gap = gap/3 + 1;
		for(i = gap;i < currentsize; i++)
		{
			if(Data[i - gap] > Data[i])
			{
				tmp = Data[i];
				for(j = i;j >= gap && tmp < Data[j - gap];j -= gap)
					Data[j] = Data[j - gap];
				Data[j] = tmp;
			}
		}
	}
}

//Stable
template<typename T>
void DataList<T>::BubbleSort()
{
	int i,j;
	for(i = 1;i < currentsize; ++i)
		for(j = currentsize - 1 ;j >= i; --j)
			if(Data[j - 1] > Data[j])
				swap(Data[j - 1] , Data[j]);
}

template<typename T>
void DataList<T>::BubbleSort_I()
{
   /*  int i,j; */
	// bool exchange = false;
	// int count = 0;
	// for(i = 1;i < currentsize; ++i)
	// {
		// for(j = currentsize - 1;j >= i ;--j)
		// {
			// if(Data[j - 1] > Data[j])
			// {
				// swap(Data[j - 1],Data[j]);
				// exchange = true;
			// }
		// }
		// count++;
		// if(exchange == false)
			// return;
	/* } */
	int i,j,high;
	// int count = 0;
	high = currentsize;
	bool sorted = false;
	while(high > 1 && sorted == false)
	{
		sorted = true;
		for(i = 1;i < high;i++)
		{
			if(Data[i - 1] > Data[i])
			{
				swap(Data[i - 1],Data[i]);
				j = i;
				sorted = false;
			}
		}
		high = j;
		// count++;
	}
	// std::cout<<count<<std::endl;
}

template<typename T>
void DataList<T>::CocktailSort()
{
	int low = 1,high = currentsize;
	int i,j;
	bool sorted = false;
	// int count = 0;
	while(sorted == false && low < high)
	{
		sorted = true;
		for(i = low;i < high;i++)
		{
			if(Data[i] < Data[i - 1])
			{
				swap(Data[i],Data[i - 1]);
				j = i;
				sorted = false;
			}
		}
		// Traverse();
		// count++;
		high = j;
		for(i = high;i >= low ;i--)
		{
			if(Data[i] < Data[i - 1])
			{
				swap(Data[i],Data[i - 1]);
				j = i;
				sorted = false;
			}
		}
		// Traverse();
		// count++;
		low = j;
	}
	// std::cout<<count<<std::endl;
}

// Simply choose the first element as basevalue,and only one direction.
template<typename T>
int DataList<T>::Partition_Left(const int &left,const int &right)
{
	int pivotpos = left;
	Element<T> pivot = Data[left];
	for(int i = left + 1;i <= right; ++i)
		if(Data[i] < pivot)
		{
			//avoid in-place exchange 
			if(++pivotpos != i)
				// Data[pivotpos] = Data[i];//only swap works,if using assignment,the value bigger than pivot will lost.
				swap(Data[pivotpos],Data[i]);
		}
	swap(Data[left],Data[pivotpos]);
	Traverse();
	std::cout<<std::endl;
	return pivotpos + 1;
}

template<typename T>
int DataList<T>::Partition_Random(const int &left,const int &right)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	int pivotpos,low,high;
	Element<T> pivot;
	pivotpos = mt() % (right - left) + left;
	pivot = Data[pivotpos];
	swap(Data[left],pivot);
	low = left;
	high = right;
	while(low < high)
	{
		while(low < high && Data[high] >= pivot)
			high--;
		Data[low] = Data[high];
		while(low < high && Data[low] <= pivot)
			low++;
		Data[high] = Data[low];
	}
	Data[low] = pivot;
	return low + 1;
}
template<typename T>
int DataList<T>::Partition_Medium3(DataList<T> &L,const int &left,const int &right)
{
	int low = left,high = right,k;
	int mid = (low + high)/2;
	Element<T> pivot;
	//choose the medial value among left,mid and right.
	k = (L[low] > L[high])?low:high;
	if(L[mid] < L[k])
		swap(L[mid],L[k]);
	if(L[low] > L[high])
		swap(L[low],L[high]);
	//ascending order:low,high,mid.
	//put the basevalue in the right position.
	pivot = L[high];
	// Traverse();
	while(low < high)
	{
		while(low < high && L[low] <= pivot)
			low++;
		L[high] = L[low];
		// std::cout<<"-> :";Traverse();
		while(low < high && L[high] >= pivot)
			high--;
		L[low] = L[high];
		// std::cout<<"<- :";Traverse();
	}
	L[low] = pivot;
	// Traverse();
	// std::cout<<std::endl;
	return low + 1;
}

//assume the pivot is the most repeating element in the sequence.
template<typename T>
void DataList<T>::Partition_Repeat(DataList<T> &L,const int &left,const int &right,int &i,int &j)
{
	int p = left - 1,q = right - 1,r;
	//choose basevalue
	int k = (L[left - 1] > L[right - 1]) ? left - 1: right - 1;
	if(L[(p + q)/2] < L[k] && q - p != 1)
		swap(L[(p + q)/2],L[k]);
	if(L[right - 1] < L[left - 1] )
		swap(L[left - 1],L[right - 1]);
	Element<T> pivot = L[right - 1];
	i = left - 1,j = right - 1;
	q--;
	j--;
	while(p < q)
	{
		while(p < q && L[p] < pivot)
			p++;
		while(p < q && L[q] > pivot)
			q--;
		if(p < q)
		{
			if(L[p] != L[q])
				swap(L[p],L[q]);
			if(p < q && L[p] == pivot)
			{
				swap(L[i],L[p]);
				i++;
				p++;
			}
			if(p < q && L[q] == pivot)
			{
				swap(L[j],L[q]);
				j--;
				q--;
			}	
		}
	}
	r = right - 1;
	if(L[p] > pivot)
	{
		swap(L[right - 1],L[p]);
		p++;
		q--;
		r--;
	}
	while(r > j)
	{
		//if this if-statement is absent,it will cause infinite loop in such situation:there are two elements in this loop,and right is bigger than left,than r is the right,and swap with the left.
		if(right - left != 1)
			swap(L[r],L[p]);
		r--;
		p++;
	}
	for(r = left - 1;r < i;r++,q--)
		swap(L[r],L[q]);
	i = q + 1;
	j = p + 1;
}

template<typename T>
void DataList<T>::QuickSort()
{
	int n = 2*currentsize;
	int *queue = new int[n];
	int front = 0,rear = 0;
	int left,right,pivotpos;
	rear = (rear + 1) % n;
	queue[rear] = 0;
	rear = (rear + 1) % n;
	queue[rear] = currentsize - 1;
	while(front != rear)
	{
		front = (front + 1) % n;
		left = queue[front];
		front = (front + 1) % n;
		right = queue[front];
		if(left < right)
		{
			pivotpos = Partition_Medium3(*this,left,right);
			rear = (rear + 1) % n;
			queue[rear] = left;
			rear = (rear + 1) % n;
			queue[rear] = pivotpos - 2;
			rear = (rear + 1) % n;
			queue[rear] = pivotpos ;
			rear = (rear + 1) % n;
			queue[rear] = right;
		}
	}
	delete [] queue;
}

template <typename T>
void DataList<T>::QuickSort(DataList &L,const int &left,const int &right)
{
	if(left < right)
	{
		// int pivotpos = Partition_Left(left - 1,right - 1);
		// int pivotpos = Partition_Repeat(L,left - 1,right - 1);		
		/* int pivotpos = Partition_Random(left - 1,right - 1); */
		// QuickSort(L,left,pivotpos - 1);
		/* QuickSort(L,pivotpos + 1,right); */
		int i = 0,j = 0;
		Partition_Repeat(L,left,right,i,j);
		QuickSort(L,left,i);
		QuickSort(L,j ,right);
	}
}

template <typename T>
void DataList<T>::Quick_Insert_Mixed_Sort(DataList &L,const int &left,const int &right)
{
	if(right - left <= THRESH_Q_I)
		InsertSort();
	else
	{
		int pivotpos = Partition(L,left - 1,right - 1);
		Quick_Insert_Mixed_Sort(L,left,pivotpos - 1);
		Quick_Insert_Mixed_Sort(L,pivotpos + 1,right);
	}
}

template <typename T>
void DataList<T>::Quick_Sort_Part(DataList &L,const int &left,const int &right)
{
	if(right - left <= THRESH_Q_I)
		return;
	else
	{
		int pivotpos = Partition(L,left - 1,right - 1);
		Quick_Sort_Part(L,left,pivotpos - 1);
		Quick_Sort_Part(L,pivotpos + 1,right);
	}
}

template<typename T>
void DataList<T>::HybirdSort(DataList<T> &L,const int &left,const int &right)
{
	Quick_Sort_Part(L,left,right);
	InsertSort();
}


template<typename T>
void DataList<T>::SelectSort()
{
	for(int i = 0;i < currentsize;i++)
	{
		int k = i;
		for(int j = i + 1;j < currentsize;j++)
			if(Data[j] < Data[k])
				k = j;
		swap(Data[k],Data[i]);
	}
}

template<typename T>
void DataList<T>::siftupmin(const int &bottom,const int &top)
{
	int child,parent;
	Element<T> tmp = Data[bottom];
	child = bottom;
	parent = (child - 1)/2;
	while(child > top && Data[parent] < tmp)
	{
		swap(Data[parent],Data[child]);
		parent = (parent - 1) / 2;
		child = parent;
	}
}

template<typename T>
void DataList<T>::siftupmax(const int &bottom,const int &top)
{
	int child,parent;
	Element<T> tmp = Data[bottom];
	child = bottom;
	parent = (child - 1)/2;
	while(child > top && Data[parent] > tmp)
	{
		swap(Data[parent],Data[child]);
		parent = (parent - 1) / 2;
		child = parent;
	}
}
	
template<typename T>
void DataList<T>::siftdownmin(const int &bottom,const int &top)
{
	int child,parent;
	Element<T> tmp = Data[top];
	parent = top;
	child = 2 * top + 1;
	while(child <= bottom)
	{
		if(child + 1 <= bottom && Data[child] > Data[child + 1])
			child++;
		if(tmp <= Data[child])
			break;
		else
		{
			swap(Data[parent],Data[child]);
			parent = child;
			child = 2 * child + 1;
		}
	}
}

template<typename T>
void DataList<T>::siftdownmax(const int &bottom,const int &top)
{
	int child,parent;
	Element<T> tmp = Data[top];
	parent = top;
	child = 2 * top + 1;
	while(child <= bottom)
	{
		if(child + 1 <= bottom && Data[child] < Data[child + 1])
			child++;
		if(tmp >= Data[child])
			break;
		else
		{
			swap(Data[parent],Data[child]);
			parent = child;
			child = 2 * child + 1;
		}
	}
}

template<typename T>
void DataList<T>::MinHeapSort()
{
	int i;
	for(i = currentsize / 2;i >= 0;i--)
		siftdownmin(currentsize - 1,i);
	i = currentsize - 1;
	while(i > 0)
	{
		swap(Data[0],Data[i--]);
		if(i > 0)
			siftdownmin(i,0);
	}
}

template<typename T>
void DataList<T>::MaxHeapSort()
{
	for(int i = currentsize / 2;i >= 0;i--)
		siftdownmax(currentsize - 1,i);
	for(int i = currentsize - 1;i > 0;i--)
	{
		swap(Data[0],Data[i]);
		if(i - 1 > 0)
			siftdownmax(i - 1,0);
	}
}

template<typename T>
void DataList<T>::SCountingSort()
{
	int count;
	Element<T> *result = new Element<T>[currentsize];
	for(int i = 0;i < currentsize;i++,count = 0)
	{
		for(int j = 0;j < currentsize;j++)
			if(Data[i] > Data[j])
				count++;
		result[count] = Data[i];
	}
	for(int i = 0;i < currentsize;i++)
		Data[i] = result[i];
}


//optimization:
//1)we dont need to re-contest all remaining player in each round.Need to avoid the death node(the root of tree is maxvalue)
template<typename T>
void DataList<T>::TournamentSort()
{
	int i,j,n,k = 0;
	n = currentsize;
	//the number of interior node equals to exterior node minus one.
	CBTree<int> Winner;
	CBTree<Element<T>> Player(n);
	//init 
	for(i = 0;i < n - 1;i++)
		Winner.Insert(0);
	for(i = 0;i < n;i++)
		Player.Insert(Data[i]);
	if(n == 1)
		return;
	//The sort process ends when the root node equals to maxvalue.
	while(1)
	{
	//play begin at the last extorior node every time.
	//when the two player have the same key value,the left child win to make the sort method stable.
	//the node num is odd or even control the way to find brother(competitor) and parent(winner)
		if(n % 2 == 0)
		{
			//Audition race determines the entries.
			for(i = n - 1;i >= 1;i -= 2)
			{
				//j is index of parent(winner of two player),i is the player.
				j = (i + n)/2 - 1;
				if(i % 2 == 0)
					Winner[j] = Player[i] <= Player[i + 1] ? i : i + 1;
				else
					Winner[j] = Player[i - 1] <= Player[i] ? i - 1 : i;
			}
			//Elimination matches determine the final winner.
			for(i = n - 2;i > 0;i -= 2)
			{
				j = (i - 1) / 2;
				if (i % 2 == 0)
					Winner[j] = Player[Winner[i - 1]] <= Player[Winner[i]] ? Winner[i - 1]: Winner[i];
				else
					Winner[j] = Player[Winner[i]] <= Player[Winner[i + 1]] ? Winner[i] : Winner[i + 1];
			}
		}
		//the same as above
		else
		{
			for(i = n - 1;i >= 0;i -= 2)
			{
				j = (i + n)/2 - 1;
				if(i == 0)
					Winner[j] = Player[Winner[n - 2]] <= Player[i] ? Winner[n - 2] : i;
				else if(i % 2 != 0)
					Winner[j] = Player[i] <= Player[i + 1] ? i : i + 1;
				else
					Winner[j] = Player[i - 1] <= Player[i] ? i - 1 : i;
			}
			//the last interior was handled in the last round of exterior,so begin from the second last node
			for (i = n - 3; i >= 1;i -= 2)
			{
				j = (i - 1) / 2;
				if(i % 2 == 0)
					Winner[j] = Player[Winner[i - 1]] <= Player[Winner[i]]? Winner[i - 1]: Winner[i];
				else
					Winner[j] = Player[Winner[i]] <= Player[Winner[i + 1]]? Winner[i] : Winner[i + 1];
			}
		}
	//after the compete,the final winner arises.
	//if final winner is maxvalue,it implys that all the players are sorted.
	if(Player[Winner[0]] == maxvalue)
		break;
	//insert the winner
	Data[k++] = Player[Winner[0]];
	//change the winner ndoe to maxvalue to begin the next round.
	Player[Winner[0]]= maxvalue;
	}
}

template<typename T>
void DataList<T>::Merge(const int &left,const int &mid,const int &right)
{
	Element<T> *tmp = new Element<T>[right - left];
	int i = left - 1,j = mid,k = 0;
	while(i < mid && j < right)
	{
		if(Data[i] <= Data[j])
			tmp[k++] = Data[i++];
		else
			tmp[k++] = Data[j++];
	}
	while(i < mid)
		tmp[k++] = Data[i++];
	while(j < right)
		tmp[k++] = Data[j++];
	for(i = right - 1,k--;i >= left - 1;i--,k--)
		Data[i] = tmp[k];
	delete [] tmp;
}

template<typename  T>
void DataList<T>::MergeSort(const int &left,const int &right)
{
	if(left >= right)
		return;
	int i = (left + right)/2;
	MergeSort(left,i);
	MergeSort(i + 1,right);
	Merge(left,i,right);
}

template<typename T>
void DataList<T>::MergeSort()
{
	int i;
	int len = 2;
	while(len <= currentsize/2)
	{
		for(i = 1;i <= currentsize - len + 1;i = i + len)
			Merge(i,(i + i + len - 1) / 2,i + len - 1);
		len *= 2;
	}
	if(currentsize % 2 != 0)
		Merge(currentsize/2 + 1,currentsize - 1,currentsize);
	Merge(1,currentsize/2,currentsize);
}
//queue is better
template<typename T>
void DataList<T>::lsd(const int &bit,const int &scale)
{
	LinkedList<Element<T>> *container;
	int n,i,j,k,scar;
	container = new LinkedList<Element<T>> [scale];
	n = currentsize;
	for(i = 1;i <= bit;i++)
	{
		 for(j = 0;j < n;j++)
		 {
			 if(Data[j] >= pow(10,i - 1))
			 	scar = Data[j].key / static_cast<int>(pow(10,i - 1)) % 10;
			else
				scar = 0;
			container[scar].push_back(Data[j]);
		 }
		 for(j = 0,k = 0;k < scale;k++)
		 	while(!container[k].isempty())
				container[k].pop_forward(Data[j++]);
	}
	delete [] container;
}

template<typename T>
void DataList<T>::LSD(const int &scale)
{
	int pbit = 1,tmpbit;
	T tmpb;
	for(int i = 0;i < currentsize;i++)
	{
		tmpb = Data[i].key;
		tmpbit = 0;
		while(tmpb != 0)
		{
			tmpbit++;
			tmpb /= 10;
		}
		if(tmpbit > pbit)
			pbit = tmpbit;
	}
	lsd(pbit,scale);
}
template<typename T>
void DataList<T>::msd(Queue<Element<T>> &Q,const int &bit,const int &scale)
{
	if(Q.IsEmpty() || bit < 1)
		return;
	Queue<Element<T>> *container;
	Element<T> tmp;
	int n,j,k,scar;
	container = new Queue<Element<T>> [scale];
	n = Q.Size();
	for(j = 0;j < n;j++)
	{
		Q.Dequeue(tmp);
		 if(tmp >= pow(10,bit - 1))
		 	scar = static_cast<int>(tmp.key) / static_cast<int>(pow(10,bit - 1)) % 10;
		else
			scar = 0;
		container[scar].Enqueue(tmp);
	}
	for(j = 0;j < scale;j++)
		msd(container[j],bit - 1,scale);
	for(j = 0,k = 0;k < scale;k++)
 		while(!container[k].IsEmpty())
		{
			container[k].Dequeue(tmp);
			Q.Enqueue(tmp);
		}
	delete [] container;
}

template<typename T>
void DataList<T>::MSD(const int &bit,const int &scale)
{
	Queue<Element<T>> container;
	for(int i = 0;i < currentsize;i++)
		container.Enqueue(Data[i]);
	msd(container,bit,scale);
	for(int i = 0;i < currentsize;i++)
		container.Dequeue(Data[i]);
}

template<typename T>
void DataList<T>::MSD(const int &scale)
{
	int pbit = 1,tmpbit;
	T tmpb;
	for(int i = 0;i < currentsize;i++)
	{
		tmpb = Data[i].key;
		tmpbit = 0;
		while(tmpb != 0)
		{
			tmpbit++;
			tmpb /= 10;
		}
		if(tmpbit > pbit)
			pbit = tmpbit;
	}
	MSD(pbit,scale);
}
	
template<typename T>
void DataList<T>::BucketSort()
{
	if(currentsize < 2)
		return;
	SeqList<Element<T>> *bucket;
	int i,j,k,l,n,div;
	long long int dist;
	Element<T> max,min;
	Element<T> tmp;
	n = currentsize;
	div = 10;//interval
	bucket = new SeqList<Element<T>> [div];
	Data[0] > Data[1] ? min = Data[1],max = Data[0] : min = Data[1],max = Data[0];
	for(i = 2;i < n - 1;i++)
	{
		if(Data[i] > Data[i + 1])
		{
			if(Data[i] > max)
				max = Data[i];
			if(Data[i + 1] < min)
				min = Data[i + 1];
		}
		else
		{
			if(Data[i] < min)
				min = Data[i];
			if(Data[i + 1] > max)
				max = Data[i + 1];
		}
	}
	dist = (max.key - min.key) / div + 1;
	//diliver elements into div buckets.
	for(i = 0;i < n;i++)
		bucket[static_cast<long long int>(Data[i].key - min.key) / dist].Insert(Data[i]);
	//insert sort to sort all the bucket
	for(j = 0;j < div;j++)
	{
		if(!bucket[j].IsEmpty())
		{
			k = bucket[j].Size();
			// std::cout<<k<<std::endl;
			// bucket[j].Traverse();
			// insert sort
			for(i = 1;i < k;i++)
			{
				if(bucket[j][i - 1] > bucket[j][i])
				{
					tmp = bucket[j][i];
					for(l = i;l >= 1 && tmp < bucket[j][l - 1];l--)
						bucket[j][l] = bucket[j][l - 1];
					bucket[j][l] = tmp;
				}
			}
			// bucket[j].Traverse();
			// std::cout<<std::endl;
		}
	}
	//push back to the origin.
	for(j = 0,i = 0;j < div;j++)
		while(!bucket[j].IsEmpty())
			Data[i++] = bucket[j].RemovePos(1);
	delete [] bucket;
}

template<typename T>
void DataList<T>::CountingSort()
{
	if(currentsize <= 1)
		return;
	int *index,i,n,size;
	Element<T> *container,max,min;
	n = currentsize;
	Data[0] > Data[1] ? max = Data[0],min = Data[1] : max = Data[1],min = Data[0];
	for(i = 2;i < n - 1;i++)
	{
		if(Data[i] > Data[i + 1])
		{
			if(Data[i] > max)
				max = Data[i];
			if(Data[i + 1] < min)
				min = Data[i + 1];
		}
		else
		{
			if(Data[i + 1] > max)
				max = Data[i + 1];
			if(Data[i] < min)
				min = Data[i];
		}
	}
	size = static_cast<int>(max.key - min.key) + 1;
	index = new int [size];
	std::memset(index,0,sizeof(int) * size);
	container = new Element<T> [n];
	//count num
	for(i = 0;i < n;i++)
		index[Data[i].key - min.key]++;
	//count final position 
	for(i = 1;i < size;i++)
		index[i] += index[i - 1];
	//sort,from tail to head to make stable,opposite dirtection also works,but not so concise.
	for(i = n - 1 ;i >= 0;i--)
		container[(index[Data[i].key - min.key]--) - 1] = Data[i];
	for(i = 0;i < n;i++)
		Data[i] = container[i];
	delete [] index;
	delete [] container;
}
template<typename T>
int DataList<T>::DivKSearch(const T &x,const int &k)
{
	int low,high,size,mid,dist;
	size = currentsize;
	high = currentsize;
	low = 0;
	while(low <= high)
	{
		dist = size / k;
		if(dist > 0)
		{
			for(int i = dist - 1;i < size;i += dist)
			{
				if(Data[i] == x)
					return i;
				else if(Data[i] > x)
					high = i;
				else
					low = i;
			}
			size = high - low + 1;
		}
		else
		{
			while(low <= high)
			{
				mid = (low + high) / 2;
				if(Data[mid] == x)
					return mid;
				else if(Data[mid] > k)
					high = mid -1;
				else
					low = mid + 1;
			}
		}
	}
	std::cout<<"Not Found!"<<std::endl;
	return -1;
}

template<typename T>
Element<T> DataList<T>::FindK(const int &left,const int &right,const int &k)
{
	if(k < 1 || k > currentsize)
		return NULL;
	int pivotpos = Partition_Random(left - 1,right - 1);
	while(pivotpos != k)
	{
		if(pivotpos > k)
			pivotpos = Partition_Random(left - 1,pivotpos - 1);
		else
			pivotpos = Partition_Random(pivotpos + 1,right - 1);
	}
	std::cout<<Data[k]<<std::endl;
	return Data[k];
}

#endif
