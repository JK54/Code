#include "../Include/Heap_Array.hpp"

using namespace std;

int main()
{
	MinHeap<int> aaa;
	MaxHeap<int> bbb;
	int i;
	int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	aaa.CreateHeap(a,sizeof(a)/sizeof(a[0]));
	bbb.CreateHeap(a,sizeof(a)/sizeof(a[0]));
	aaa.TraverseLevelOrder();
	bbb.TraverseLevelOrder();
	cout<<endl;
	aaa.Remove(i);
	aaa.TraverseLevelOrder();
	cout<<endl;
	aaa.Remove(i);
	aaa.TraverseLevelOrder();
	cout<<endl;
	bbb.Remove(i);
	bbb.TraverseLevelOrder();
	cout<<endl;
	bbb.Remove(i);
	bbb.TraverseLevelOrder();
	cout<<endl;
}
