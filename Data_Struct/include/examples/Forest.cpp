#include "../Forest.h"

using namespace std;

int main()
{
	Tree<int> aaa;
	aaa.SetFlag(32767,0);
	ifstream is("forest.txt");
	aaa.CreateTree(is);
	aaa.Traverse(aaa.Root());
}
