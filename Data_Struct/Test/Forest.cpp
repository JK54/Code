#include "../Include/Forest.hpp"

using namespace std;
int main()
{
	ifstream is("./forest.txt");
	ifstream is2("./forest.txt");
// set the nextrother mark and frichild mark of tree<int>
	Tree<int>::SetFlag(32767,0);
	Forest<int> fff;
	fff.CreateForest(is);
	fff.DFS();
	fff.BFS();
	cout<<endl;
	Tree<int> aaa(fff.SelectTree(0));
	aaa.Traverse_RootFirst(aaa.Root());
	cout<<endl;
	cout<<aaa.Search(aaa.Root(),1)<<endl;
	cout<<endl;
	aaa.PrintBranch(aaa.Root());
	cout<<endl;
	BinTree<int> bbb(aaa.Tran2Bint(aaa.Root()));
	bbb.TraversePreOrder(bbb.Root(),1);
	cout<<endl;
	Tree<int> ccc(aaa.Build4Bint(bbb.Root()));
	ccc.Traverse_RootFirst(ccc.Root());
	cout<<endl;
	cout<<endl;
//convert to bintree
	BinTreeNode<int> *tmp = fff.Tran2Bin();
	BinTree<int> ddd(tmp);
	ddd.TraversePreOrder(ddd.Root(),1);
	cout<<endl;
	fff.Build4Bin(ddd.Root());
	fff.DFS();
}
