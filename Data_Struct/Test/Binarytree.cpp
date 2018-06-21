#include "../Include/BinaryTree.hpp"

using namespace std;

int main()
{
	BinTree<int> bbb;
	bbb.SetMark(0);
	BinTreeNode<int> *b = bbb.Root();
	ifstream is("binarytree.txt");
	bbb.CreateTreePreOrder(b,is);
	BinTree<int> aaa;
	// aaa.TraversePreOrder(b,1);
	// std::cout<<endl;
	// aaa.TraverseInOrder(b);
	// std::cout<<endl;
	// aaa.TraversePostOrder(b);
	// std::cout<<endl;
	// aaa.TraverseLevelOrder(b);
	/* std::cout<<endl; */
	int preo[] = {1,2,4,5,3,6,7};
	int ino[] = {8,4,2,5,1,6,3,7};
	int posto[7] = {0};
	int pro[] = {1,2,4,8,9,5,10,11,3,6,12,7};
	int io[] = {8,4,9,2,10,5,11,1,6,12,3,7};
	BinTreeNode<int> *p = CreateTreeByPreInOrder(pro,io,12);
   /*  aaa.TraverseLevelOrder(p); */
	// std::cout<<endl;
	// aaa.TraversePreOrder_NR1(p);
	// std::cout<<endl;
	// aaa.TraverseInOrder_NR(p);
	// std::cout<<endl;
	/* aaa.TraversePostOrder_NR(p); */
	aaa.Copy(p);
	BinTreeNode<int> *q = aaa.Root();
	aaa.TraverseDoubleOrder(q);
	cout<<endl;
	aaa.TraverseLevelOrder(q);
	cout<<endl;
	aaa.TraversePreOrder_NR1(q);
	cout<<endl;
	aaa.TraverseInOrder(q);
	cout<<endl;
	aaa.TraversePostOrder_NR(q);
	cout<<endl;
	cout<<aaa.IsCBT(q)<<endl;
	aaa.TransPre2Post(preo,posto,0,6,0,6);
	for(int i = 0;i<7;i++)
		cout<<posto[i]<<" ";
	cout<<endl;
}
