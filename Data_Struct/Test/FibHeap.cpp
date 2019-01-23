#include "../Include/Fibonacci_Heap.hpp"

int main()
{
	MinFibHeap<int> aaa,bbb;
	aaa.Insert(3);
	bbb.Insert(2);
	aaa.Union(bbb);
	aaa.Extract_Min();
	for(int i = 4;i < 15;i++)
		aaa.Insert(i);
	aaa.Extract_Min();
	aaa.Insert(1);
	aaa.Decrease_Key(aaa.Min()->right,0);
	aaa.Delete(aaa.Min(),-1);
	return 0;
}
