#include "linkedlist.h"
#include <iostream>
ListNode* create(int data[],int n)
{
	ListNode *pre,*cur,*head;
	if(n <= 0)
		return nullptr;
	head = new ListNode;
	head->m_nValue = data[0];
	head->m_pNext = nullptr;
	pre = head;
	for(int i = 1;i < n;i++)
	{
		cur = new ListNode;
		cur->m_nValue = data[i];
		cur->m_pNext = nullptr;
		pre->m_pNext = cur;
		pre = cur;
	}
	return head;
}

void traverse(ListNode *p)
{
	while(p != nullptr)
	{
		std::cout<<p->m_nValue<<" ";
		p = p->m_pNext;
	}
	std::cout<<std::endl;
}

void destroy(ListNode *p)
{
	ListNode *cur = p;
	while(cur != nullptr)
	{
		ListNode *next = cur->m_pNext;
		delete cur;
		cur = next;
	}
}
