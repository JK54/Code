#include "../Include/Fibonacci_Heap.hpp"

int main()
{
	MinFibHeap<int> aaa,bbb;
	aaa.Insert(1);
	bbb.Insert(2);
	aaa.Union(bbb);
	return 0;
}
