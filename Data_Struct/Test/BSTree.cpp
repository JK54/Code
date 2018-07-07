#include "../Include/BSTree.hpp"

using namespace std;

int main()
{
	BSTree<int> aaa(6);
	int arr2[] = {2,4,5,8,9,10,12,15,16,17,18,19};
	BinTreeNode<int> *&a = aaa.BSTree<int>::BinTree<int>::Root();
	aaa.CreateTreeByIncSeq(a,1,12,arr2);
	aaa.TraverseLevelOrder(a);
	cout<<endl;
	aaa.TraverseInOrder(a);
	cout<<endl;
	aaa.RemoveLessThanX(a,12);
	aaa.TraverseInOrder_NR(a);
	cout<<endl;
}
