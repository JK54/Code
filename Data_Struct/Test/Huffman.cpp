#include "../Include/HuffmanTree.hpp"

using namespace std;

int main()
{
	int a[6] = {1,2,3,4,5,6};
	int b[6] = {6,5,4,3,2,1};
	Huffman<int,int> aaa;
	aaa.Hu_Tucker(a,b,6);
	aaa.Traverse(aaa.Root());
	cout<<endl;
}
