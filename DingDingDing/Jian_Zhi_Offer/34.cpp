#include "tree.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

bool isleaf(TreeNode *p)
{
	if(p == nullptr)
		return false;
	if(p->lchild == nullptr && p->rchild == nullptr)
		return true;
	return false;
}

void printpath(vector<int> path)
{
	for(vector<int>::iterator p = path.begin(); p != path.end();++p)
		cout<<*p<<" ";
	cout<<endl;
}

void Path(TreeNode *p,int value,vector<int> &path,int cursum)
{
	cursum += p->key;
	path.push_back(p->key);
	if(isleaf(p) && cursum == value)
		printpath(path);
		// cout<<cursum<<std::endl;
	if(p->lchild != nullptr)
		Path(p->lchild,value,path,cursum);
	if(p->rchild != nullptr)
		Path(p->rchild,value,path,cursum);
	path.pop_back();
}

void  FindPath(TreeNode *p,int value)
{
	if(p == nullptr)
		return;
	vector<int> path;
	int cursum = 0;
	Path(p,value,path,cursum);
}
int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int ain[]  = {5,3,6,2,4,1,7,8,11,12,10,9};
	Tree a(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));
	a.traverse();
	cout<<endl;
	a.traverselevelbylevel();
	cout<<endl;
	for(int i = 1;i < 59;i++)
		FindPath(a.root,i);
}
