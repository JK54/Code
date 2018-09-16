#include "../Include/HuffmanTree.hpp"

using namespace std;

int main()
{
	int a[6] = {1,2,3,4,5,6};
	int b[6] = {8,5,4,1,2,7};
	Huffman<int,int> aaa;
	aaa.CreateTree(a,b,6);
	aaa.TraversePreOrder(aaa.Root());
	cout<<endl;
	aaa.TraverseInOrder(aaa.Root());
	cout<<endl;
	aaa.TraversePostOrder(aaa.Root());
	cout<<endl;
	cout<<aaa.WPL()<<endl;
	return 0;
}
