#include <iostream>
#include "linkedlist.h"

ListNode *compare(ListNode **pa,ListNode **pb)
{
	ListNode *p;
	if((*pa)->m_nValue > (*pb)->m_nValue)
	{
		p = *pb;
		*pb = (*pb)->m_pNext;
	}
	else
	{
		p = *pa;
		*pa = (*pa)->m_pNext;
	}
	return p;
}
ListNode *combound(ListNode *pa,ListNode *pb)
{
	if(pa == nullptr)
		return pb;
	if(pb == nullptr)
		return pa;
	ListNode *head,*trav,*pre;
	head = compare(&pa,&pb);
	pre = head;
	while(pa != nullptr && pb != nullptr)
	{
		trav = compare(&pa,&pb);
		trav->m_pNext = pre->m_pNext;
		pre->m_pNext = trav;
		pre = trav;
	}
	trav->m_pNext = (pa == nullptr) ? pb : pa;
	return head;
}

ListNode *combound2(ListNode *pa,ListNode *pb)
{
	if(pa == nullptr)
		return pb;
	if(pb == nullptr)
		return pa;
	ListNode *head = nullptr;
	if(pa->m_nValue > pb->m_nValue)
	{
		head = pb;
		head->m_pNext = combound2(pa,pb->m_pNext);
	}
	else
	{
		head = pa;
		head->m_pNext = combound2(pa->m_pNext,pb);
	}
	return head;
	
}

int main()
{
	int a[] = {1,3,5,7,9,15};
	int b[] = {2,4,6,8,10,11,12,13,14};
	int alen = sizeof(a) / sizeof(a[0]);
	int blen = sizeof(b) / sizeof(b[0]);
	ListNode *pa,*pb,*pc;
	pa = create(a,alen);
	pb = create(b,blen);
	traverse(pa);
	traverse(pb);
	pc = combound(pa,pb);
	traverse(pc);
	destroy(pc);
	return 0;
}

