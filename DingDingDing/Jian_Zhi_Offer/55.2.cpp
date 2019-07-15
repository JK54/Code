#include <iostream>
#include "stack.hpp"
#include "tree.h"

bool isbanlanced(TreeNode *p,int &deep)
{
	if(p == nullptr)
	{
		deep = 0;
		return true;
	}
	int left,right;
	if(isbanlanced(p->lchild,left) && isbanlanced(p->rchild,right))
	{
		int diff = abs(left - right);
		if(diff <= 1)
		{
			deep = std::max(left,right) + 1;
			return true;
		}
	}
	return false;
}

//未完成
bool isbanlanced2(TreeNode *p)
{
	if(p == nullptr)
		return false;
	Stack<TreeNode*> st;
	TreeNode *pre,*trav;
	pre = nullptr;
	trav = p;
	while(trav != nullptr)
	{
		st.push(trav);
		trav = trav->lchild;
	}
	while(st.size() != 0)
	{
		trav = st.top();
		st.pop();
		if(trav->rchild == nullptr || trav->rchild == pre)
		{
			std::cout<<trav->key<<" ";
			pre = trav;

		}
		else
		{
			st.push(trav);
			trav = trav->rchild;
			while(trav != nullptr)
			{
				st.push(trav);
				trav = trav->lchild;
			}
		}
	}
	return true;
}

int main()
{
	int apre[] = {1,2,4,5,7,3,6};
	int ain[]  = {4,2,7,5,1,3,6};
	int bpre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int bin[]  = {5,3,6,2,4,1,7,8,11,12,10,9};
	Tree aaa(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));
	Tree bbb(bpre,bin,sizeof(bpre) / sizeof(bpre[0]),sizeof(bin) / sizeof(bin[0]));
	int da = 0,db = 0;
	std::cout<<isbanlanced(aaa.root,da)<<std::endl;
	std::cout<<isbanlanced(bbb.root,db)<<std::endl;
	std::cout<<isbanlanced2(aaa.root)<<std::endl;
	std::cout<<isbanlanced2(bbb.root)<<std::endl;
}
