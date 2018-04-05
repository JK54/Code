#include "../Include/MinHeap.hpp"
using namespace std;

int main()
{
	ifstream is1("heap1.txt");
	ifstream is2("heap2.txt");
	Queue<int> q;
	int i;
	while(is1>>i)
		q.Enqueue(i);
	MinHeap<int> hp(q);
	hp.TraverseLevelOrder();
	while(is2>>i)
		hp.Insert(i);
	hp.TraverseLevelOrder();
	hp.TraversePostOrder();
	hp.siftDown();
	hp.TraverseLevelOrder();
}
