#include "../ThreadBinaryTree.h"
#include "../BinaryTree.h"
using namespace std;

int main()
{
	int ino[] = {8,4,2,5,1,6,3,7};
	int posto[] = {8,4,5,2,6,7,3,1};
	BinTreeNode<int> *broot = CreateTreeByInPostOrder(ino,posto,sizeof(ino)/sizeof(ino[0]));
	ThreadTree<int> t;
	t.CreateInThread(broot);
	t.TraversePreOrder(t.Root());
	cout<<endl;
	t.TraverseInOrder(t.Root());
	cout<<endl;
	t.TraversePostOrder(t.Root());
	cout<<endl;
}
