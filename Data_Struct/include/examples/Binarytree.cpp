#include "../BinaryTree.h"

using namespace std;

int main()
{
	
	BinTree<int> bbb;
	bbb.SetMark(0);
	BinTreeNode<int> *b = bbb.Root();
	ifstream is("binarytree.txt");
	CreateTreePreOrder(b,is);
	BinTree<int> aaa;
	/* BinTreeNode<int> *a = aaa.Copy(bbb.Root()); */
	// aaa.TraversePreOder(b,1);
	// std::cout<<endl;
	// aaa.TraverseInOder(a);
	// std::cout<<endl;
	// aaa.TraversePostOder(a);
	/* std::cout<<endl; */
	int preo[] = {1,2,4,8,5,3,6,7};
	int ino[] = {8,4,2,5,1,6,3,7};
	int posto[] = {8,4,5,2,6,7,3,1};
	/*
	 * int ino[] = {1,2,1,2,1,2,1,1};
	 * int posto[] = {1,2,2,1,2,1,1,1};
	 */
	BinTreeNode<int> *p = CreateTreeByInPostOrder(ino,posto,8);
	aaa.TraverseLevelOrder(p);
	std::cout<<endl;
	aaa.TraversePreOder_NR1(b);
	std::cout<<endl;
	aaa.TraverseInOder_NR(b);
	std::cout<<endl;
	// aaa.TraversePostOder_NR(b);
}
