#include "../Include/CompleteBinaryTree.hpp"
#include "../Include/BinaryTree.hpp"
using namespace std;

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10,11};
	CBTree<int> aaa,ccc;
	aaa.BuildTree(a,sizeof(a)/sizeof(a[0]));
	aaa.TraversePostOrder(0);
	cout<<endl;
	aaa.PrintRelate(3);

	BinTree<int> bbb;
	bbb.Copy(aaa.ArrCBT2LinkedBST(0));
	bbb.TraversePreOrder_NR1(bbb.Root());
	cout<<endl;
	ccc.LinkedBST2ArrCBT(bbb.Root(),0);
	ccc.TraversePostOrder(0);
	cout<<endl;
}
