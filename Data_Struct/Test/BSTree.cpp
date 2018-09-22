#include "../Include/BSTree.hpp"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int main()
{
	BSTree<int> aaa;
	vector<int> a;
	a.reserve(21);
	random_device rd;
	mt19937 mt(rd());
	for(int i = 0;i < 20;i++)
	{
		a[i] = mt();
		cout<<a[i]<<" ";
	}
	cout<<endl;
	for(int i = 0 ;i < 20;i++)
		aaa.Insert(a[i]);
	aaa.TraverseInOrder(aaa.Root());
	cout<<endl;
	for(int i = 0;i < 20;i++)
	{
		aaa.Remove(a[i]);
		aaa.TraverseInOrder(aaa.Root());
		cout<<endl;
	}
	cout<<endl;
}
