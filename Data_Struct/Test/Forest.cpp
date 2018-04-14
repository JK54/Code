#include "../Include/Forest.hpp"

using namespace std;

int main()
{
	ifstream is("./forest1.txt");
	// Forest<int> fff;
	Tree<int> aaa(0);
	aaa.SetFlag(32767,0);
	aaa.CreateTree(aaa.Root(),is);
	Traverse_RootFirst(aaa.Root());
	cout<<endl;
	for(int i = 1; i<20 ;++i)
		aaa.Insert(i);
	Traverse_RootLast(aaa.Root());
	cout<<endl;
	cout<<aaa.Search(aaa.Root(),19)<<endl;
// fff.CreateForest(is);
	// fff.BFS();
}
