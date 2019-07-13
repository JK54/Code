#include <iostream>
#include "tree.h"

TreeNode* findkth(TreeNode *p,int &k)
{
	TreeNode *trav = nullptr;
	if(p->lchild != nullptr)
		trav = findkth(p->lchild,k);
	if(trav == nullptr)
	{
		if(k == 1)
			trav = p;
		k--;
	}
	if(trav == nullptr && p->rchild != nullptr)
		trav = findkth(p->rchild,k);
	return trav;
}

TreeNode* findk(TreeNode *p,int k)
{
	if(p == nullptr || k <= 0)
		return nullptr;
	return findkth(p,k);
}

int main()
{
	int a[] = {5,3,2,4,7,6,8};
	int b[] = {2,3,4,5,6,7,8};
	int size= sizeof(a) / sizeof(a[0]);
	Tree aaa(a,b,size,size);
	aaa.traverse();
	TreeNode *p = findk(aaa.root,3);
	std::cout<<p->key<<std::endl;
}
