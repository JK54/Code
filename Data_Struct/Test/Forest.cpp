#include "../Include/Forest.hpp"

using namespace std;

int main()
{
	ifstream is("./forest.txt");
	ifstream is2("./forest.txt");
	Forest<int> fff;
	fff.CreateForest(is);
	fff.DFS();
	fff.BFS();
	Tree<int> aaa(fff.SelectTree(1));
	Traverse_RootFirst(aaa.Root());
	cout<<endl;
	BinTree<int> bbb(Tran2Bint(aaa.Root()));
	bbb.TraversePreOrder(bbb.Root(),1);
	cout<<endl;
	Tree<int> ccc(aaa.Tran4Bin(bbb.Root()));
	Traverse_RootFirst(ccc.Root());
	cout<<endl;
	cout<<endl;
	BinTreeNode<int> *tmp = fff.Tran2Bin();
	BinTree<int> ddd(tmp);
	ddd.TraversePreOrder(ddd.Root(),1);
}
