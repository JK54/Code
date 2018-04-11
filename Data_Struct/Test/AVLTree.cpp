#include "../Include/AVLTree.hpp"

using namespace std;


int main()
{
	BSTree<int> aaa(0);
	ifstream is("heap1.txt");
	aaa.CreateBST(is);
	aaa.TraverseLevelOrder(aaa.Root());
	getchar();
}
