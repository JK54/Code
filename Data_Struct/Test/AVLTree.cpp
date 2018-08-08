#include "../Include/AVLTree.hpp"

using namespace std;

int main()
{
	AVLTree<int> aaa;
	/*
	 * int num;
	 * std::cin>>num;
	 */
	int a[] = {4,2,6,1,3,5,7,16,15,14,13,12,11,10,8,9};
	for(int i = 0;i < static_cast<int>(sizeof(a)/sizeof(a[0]));++i)
		aaa.Insert(a[i]);
	aaa.TraversePreOrder(aaa.Root());
	cout<<endl;
	aaa.TraverseInOrder(aaa.Root());
	std::cout<<endl;
	aaa.TraverseLevelOrder(aaa.Root());
	std::cout<<endl<<endl;
	for(int i = 0; i < static_cast<int>(sizeof(a)/sizeof(a[0]));i++)
	{
		aaa.Remove(a[i]);
		aaa.TraversePreOrder(aaa.Root());
		std::cout<<endl;
	 	aaa.TraverseInOrder(aaa.Root());
		std::cout<<endl;
		cout<<endl;
	}
	return 0;
}
