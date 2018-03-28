#include "../Forest.h"

using namespace std;

int main()
{
	ifstream is("./forest.txt");
	Forest<int> fff;
	fff.Head()->SetFlag(32767,0);
	/*
	 * Tree<int> aaa;
	 * aaa.SetFlag(32767,0);
	 * aaa.CreateTree(aaa.Root(),is);
	 * aaa.Traverse(aaa.Root());
	 * cout<<endl;
	 */
	fff.CreateForest(is);
	fff.BFS();
}
