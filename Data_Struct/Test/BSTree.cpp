#include "../Include/BSTree.hpp"

using namespace std;

int main()
{
	BSTree<int> aaa(0);
	BinTreeNode<int> *a = aaa.BSTree<int>::BinTree<int>::Root();
	for(int i = 0;i<10000;i++)
		aaa.Insert(i);
	aaa.TraverseLevelOrder(a);
	cout<<endl;
}
