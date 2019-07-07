#include <iostream>
#include <random>
#include "tree.h"

TreeNode* createbst(int a[],int n)
{
	TreeNode *result;
	if(a == nullptr || n <= 0)
		return nullptr;
	result = new TreeNode(a[0]);
	for(int i = 1;i < n;i++)
	{
		TreeNode *pre = nullptr;
		TreeNode *cur = result;
		TreeNode *tmp = new TreeNode(a[i]);
		while(cur != nullptr)
		{
			pre = cur;
			if(tmp->key > cur->key)
				cur =  cur->rchild;
			else
				cur = cur->lchild;
		}
		if(tmp->key > pre->key)
			pre->rchild = tmp;
		else
			pre->lchild = tmp;
	}
	return result;
}

void inorder(TreeNode *trav,TreeNode **lastnode)
{
	if(trav == nullptr)
		return;
	TreeNode *cur = trav;
	if(trav->lchild != nullptr)
		inorder(trav->lchild,lastnode);

	cur->lchild = *lastnode;
	if(*lastnode != nullptr)
		(*lastnode)->rchild = cur;
	*lastnode = cur;

	if(trav->rchild != nullptr)
		inorder(trav->rchild,lastnode);
}

TreeNode* tran2duallist(TreeNode *p)
{
	TreeNode *lastnode = nullptr;
	inorder(p,&lastnode);
	while(lastnode->lchild != nullptr)
		lastnode = lastnode->lchild;
	return lastnode;
}

int main()
{
	int a[16];
	int size = 16;
	// int size = sizeof(a) / sizeof(a[0]);
	std::random_device rd;
	std::mt19937 mt(rd());
	for(int i = 0;i < size;i++)
	{
		a[i] = mt() % 120;
		std::cout<<a[i]<<" ";
	}			
	std::cout<<std::endl;
	TreeNode *aaa;
	aaa = createbst(a,size);
	TreeNode *p,*pp;
	for(p = tran2duallist(aaa);p != nullptr;p = p->rchild)
	{
		std::cout<<p->key<<" ";
		pp = p;
	}
	std::cout<<std::endl;
	while(pp != nullptr)
	{
		std::cout<<pp->key<<" ";
		p = pp;
		pp = pp->lchild;
	}
	while(p != nullptr)
	{
		TreeNode *tmp = p->rchild;
		delete p;
		p = tmp;
	}
	std::cout<<std::endl;

	return 0;
}
