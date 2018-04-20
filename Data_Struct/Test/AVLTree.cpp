#include "../Include/AVLTree.hpp"

using namespace std;

int main()
{
	AVLTree<int> aaa(10);
	AVLTreeNode<int> *a = aaa.Root();
	ifstream is("bst.txt");
	aaa.CreateBST(is);
	aaa.TraverseLevelOrder(a);
	cout<<endl;
	// aaa.Remove(10,a);
	// aaa.TraverseLevelOrder(aaa.Root());
	// cout<<endl;
	// for(int i = 1; i< 31; ++i)
	// 	aaa.Insert(i);
	// aaa.TraversePreOrder(aaa.Root(),1);
	// cout<<endl;
	// aaa.TraverseLevelOrder(aaa.Root());
	// cout<<endl;
}
