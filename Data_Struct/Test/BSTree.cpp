#include "../Include/BSTree.hpp"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main()
{
	BSTree<int> aaa(0);
	for(int i = 1 ;i < 100005;i++)
		aaa.Insert(i);
	aaa.TraverseInOrder(aaa.Root());
	for(int i = 0;i < 100005;i++)
		aaa.Remove(i);
	cout<<endl;
}
