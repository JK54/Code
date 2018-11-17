#include "../Include/LinearList_linkedlist.hpp"

using namespace std;

int main()
{
	LinkedList<int> p,q;
	// LinkedList<int> i,j;
	for(int i = 1;i < 21;i += 2)
		p.push_back(i);
	for(int i = 2;i < 22;i += 2)
		q.push_back(i);
	p.Traverse();
	q.Traverse();
	p.LastK(5);
	// p.ReverseMerge(q);
	// p.Traverse();
	// p.DepartOD(i,j);
	// i.Traverse();
	// j.Traverse();

}
