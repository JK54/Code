#include "../Include/BSTree.hpp"

using namespace std;

int main()
{
	BSTree<int> aaa(6);
	int arr[] = {8,4,12,2,5,10,15,9,11,18,16,17};
	int arr2[] = {2,4,5,8,9,10,12,15,16,17,18,19};
	int arr3[] = {10,5,2};
	BinTreeNode<int> *&&a = aaa.BSTree<int>::BinTree<int>::uRoot();
	aaa.CreateTreeByIncSeq(a,1,12,arr2);
	aaa.TraverseLevelOrder(a);
	cout<<endl;
	aaa.TraverseInOrder(a);
	cout<<endl;
	aaa.RemoveMax();
	aaa.TraverseLevelOrder(a);
	cout<<endl;
	cout<<aaa.IsSearchSeq(arr3,2)<<endl;
}
