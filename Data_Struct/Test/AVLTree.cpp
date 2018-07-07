#include "../Include/AVLTree.hpp"

using namespace std;

int main()
{
	AVLTree<int> aaa;
	for(int i = 0;i<100;++i)
		aaa.Insert(i);
	cout<<aaa.Root()->Data()<<endl;
	aaa.Traverse(aaa.Root());
	cout<<endl;
	aaa.TraverseLevelOrder(aaa.Root());
	cout<<endl;
	for(int i = 1; i<100; i = i+ 5)
		aaa.Remove(i);
	aaa.Traverse(aaa.Root());
}
