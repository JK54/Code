#include <iostream>
#include "linkedlist.h"

void DeleteNode(ListNode *pListHead,ListNode *pToBeDeleted)
{
	if(pToBeDeleted->m_pNext == nullptr)
	{
		ListNode *p = pListHead;
		while(p->m_pNext != pToBeDeleted)
			p = p->m_pNext;
		p->m_pNext = nullptr;
		delete pToBeDeleted;
		//形参指针修改并无意义
		// pToBeDeleted = nullptr;
	}
	else if(pListHead == pToBeDeleted)
	{
		delete pToBeDeleted;
		// pListHead = nullptr;
		// pToBeDeleted = nullptr;
	}
	else
	{
		ListNode *p = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = p->m_nValue;
		pToBeDeleted->m_pNext = p->m_pNext;
		delete p;
		// p = nullptr;
	}
}


int main()
{
	int a[] = {1,3,5,7,8,9};
	int size = sizeof(a) / sizeof(a[0]);
	ListNode *p = create(a,size);
	traverse(p);
	ListNode *pp = p->m_pNext->m_pNext;
	DeleteNode(p,pp);
	traverse(p);
	destroy(p);
}
