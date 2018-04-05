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
	aaa.TraversePreOrder(b,1);
	std::cout<<endl;
	aaa.TraverseInOrder(b);
	std::cout<<endl;
	aaa.TraversePostOrder(b);
	std::cout<<endl;
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
	aaa.TraversePreOrder_NR1(p);
	std::cout<<endl;
	aaa.TraverseInOrder_NR(p);
	std::cout<<endl;
	aaa.TraversePostOrder_NR(p);
}
