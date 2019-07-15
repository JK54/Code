#include <iostream>
#include "linkedlist.h"

void mklist(ListNode **pa,ListNode **pb,int a[],int na,int b[],int nb,int c[],int nc)
{
	ListNode *p1,*p2,*p3,*tmp;
	p1 = create(a,na);
	p2 = create(b,nb);
	p3 = create(c,nc);
	for(tmp = p1;tmp->m_pNext != nullptr;tmp = tmp->m_pNext);
	tmp->m_pNext = p3;
	for(tmp = p2;tmp->m_pNext != nullptr;tmp = tmp->m_pNext);
	tmp->m_pNext = p3;
	*pa = p1;
	*pb = p2;
}

ListNode* commonnode(ListNode *p1,ListNode *p2)
{
	if(p1 == nullptr || p2 == nullptr)
		return nullptr;
	ListNode *tmp1,*tmp2,*result;
	int len1,len2;
	for(len1 = 0,tmp1 = p1;tmp1 != nullptr;tmp1 = tmp1->m_pNext,len1++);
	for(len2 = 0,tmp2 = p2;tmp2 != nullptr;tmp2 = tmp2->m_pNext,len2++);
	tmp1 = p1,tmp2 = p2;
	if(len1 > len2)
		for(int i = 0;i < len1 - len2;i++)
			tmp1 = tmp1->m_pNext;
	else
		for(int i = 0;i < len2 - len1;i++)
			tmp2 = tmp2->m_pNext;
	result = nullptr;
	while(result == nullptr && tmp1 != nullptr && tmp2 != nullptr)
	{
		if(tmp1 == tmp2)
			result = tmp1;
		tmp1 = tmp1->m_pNext;
		tmp2 = tmp2->m_pNext;
	}
	traverse(result);
	return result;
}

int main()
{
	int a[] = {1,3,5,7,9};
	int b[] = {2,4,6,8};
	int c[] = {10,11,12,13,14,15};
	ListNode *p1,*p2;
	mklist(&p1,&p2,a,sizeof(a) / sizeof(a[0]),b,sizeof(b)/sizeof(b[0]),c,sizeof(c) / sizeof(c[0]));
	commonnode(p1,p2);
}
