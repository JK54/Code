#include <iostream>
#include "tree.h"

bool isleaf(TreeNode *p)
{
	if(p->lchild == nullptr && p->rchild == nullptr)
		return true;
	return false;
}

int deepth(TreeNode *p)
{
	if(p == nullptr)
		return 0;
	if(isleaf(p))
		return 1;
	return 1 + std::max(deepth(p->lchild),deepth(p->rchild));
}

int main()
{
	int pre[] = {1,2,4,5,7,3,6};
	int in[]  = {4,2,7,5,1,3,6};
	Tree aaa(pre,in,sizeof(pre) / sizeof(pre[0]),sizeof(in) / sizeof(in[0]));
	std::cout<<deepth(aaa.root)<<std::endl;
}
