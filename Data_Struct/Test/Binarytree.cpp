#include "../Include/BinaryTree.hpp"

using namespace std;

int main()
{
   /*  BinTree<char> aaa; */
	// char preo1[] = {'*','+','a','b','*','c','-','d'};
	// char ino1[] = {'a','+','b','*','c','*','-','d'};
	// char preo2[] = {'+','*','a','b','-','-','c','d'};
	// char ino2[] = {'a','*','b','+','-','c','-','d'};
	// BinTreeNode<char> *p = CreateTreeByPreInOrder(preo2,ino2,sizeof(preo2)/sizeof(preo2[0]));
	// aaa.Copy(p);
	// aaa.TraverseInOrder(aaa.Root());
	// cout<<endl;
	// aaa.PrintExpression(aaa.Root());
	/* cout<<endl; */
	/* BinTree<int> bbb; */
	// bbb.SetMark(0);
	// BinTreeNode<int> *b = bbb.Root();
	// ifstream is("binarytree.txt");
	// bbb.CreateTreePreOrder(b,is);
	BinTree<int> aaa;
	// // aaa.TraversePreOrder(b,1);
	// // std::cout<<endl;
	// // aaa.TraverseInOrder(b);
	// // std::cout<<endl;
	// // aaa.TraversePostOrder(b);
	// // std::cout<<endl;
	// // aaa.TraverseLevelOrder(b);
	// [> std::cout<<endl; <]
	// int posto[7];
	// int preo[] = {1,2,4,5,6,3,7};
	int pro[] = {1,2,4,8,9,5,10,11,3,6,12,7};
	int io[] = {8,4,9,2,10,5,11,1,12,6,3,7};
	BinTreeNode<int> *p = CreateTreeByPreInOrder(pro,io,sizeof(pro)/sizeof(pro[0]));
	aaa.Copy(p);
	BinTreeNode<int> *q = aaa.Root();
	std::cout<<aaa.Height()<<std::endl;
	std::cout<<aaa.Height(q)<<std::endl;
	aaa.TraverseLevelOrder(q);
	cout<<endl;
	// aaa.TraversePreOrder_NR1(q);
	// cout<<endl;
	// aaa.TraverseInOrder(q);
	// cout<<endl;
	// aaa.TraversePostOrder_NR(q);
	// cout<<endl;
	// cout<<aaa.Size()<<endl;
	// cout<<aaa.IsCBT(q)<<endl;
	// cout<<aaa.Countn2(q)<<endl;
	// int n = 0;
	// aaa.Countn2(q,n);
	// cout<<n<<endl;
	// cout<<endl;
	/*
	 * aaa.RuinX(q,1);
	 * aaa.TraversePreOrder(q);
	 * cout<<endl;
	 * aaa.TraverseInOrder(q);
	 * cout<<endl;
	 */
	// aaa.LinkLeaf();
   // [>  aaa.TransPre2Post(preo,posto,0,6,0,6); <]
	// // for(int i = 0;i < 7;i++)
		// // cout<<posto[i]<<" ";
	/* [> cout<<endl; <] */
}
