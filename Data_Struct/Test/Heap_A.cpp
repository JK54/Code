#include "../Include/Heap_Array.hpp"

using namespace std;

int main()
{
	MinHeap<int> aaa;
	MaxHeap<int> bbb;
	int i;
	int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	for(i = 0;i < int(sizeof(a)/sizeof(a[0]));i++)
	{	
		bbb.Insert(a[i]);
		bbb.TraverseLevelOrder();
		bbb.IsHeap();
		cout<<endl;
	}
}
