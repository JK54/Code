#include <iostream>
#include <limits.h>

struct LNode
{
	int key;
	LNode *next;
	explicit LNode(int x):key(x),next(nullptr){}
};

LNode *creat(int a[],int n)
{
	LNode *head,*pre,*cur;
	if(n <= 0)
		return nullptr;
	head = new LNode(a[0]);
	pre = head;
	for(int i = 1;i < n;i++)
	{
		cur = new LNode(a[i]);
		pre->next = cur;
		pre = cur;
	}
	return head;
}

void traverse(LNode *p)
{
	while(p != nullptr)
	{
		std::cout<<p->key<<" ";
		p = p->next;
	}
	std::cout<<std::endl;
}

void deletedup(LNode **phead)
{
	if(phead == nullptr || *phead == nullptr)
		return;
	LNode *pre,*pcur;
	pre = nullptr;
	pcur = *phead;
	while(pcur != nullptr)
	{
		LNode *pnext = pcur->next;
		bool del = false;
		if(pnext != nullptr && pnext->key == pcur->key)
			del = true;
		if(!del)
		{
			pre = pcur;
			pcur = pcur->next;
		}
		else
		{
			LNode *pdel = pcur;
			int value = pcur->key;
			while(pdel != nullptr && pdel->key == value)
			{
				pnext = pdel->next;
				delete pdel;
				pdel = pnext;
			}
			if(pre == nullptr)
				*phead = pnext;
			else
				pre->next = pnext;
			pcur = pnext;
		}
	}
}

int main()
{
	int a[] = {1,1,1,2,2,2,3,4,5,5,5,6,6,6,6,7,7,7,8,9,9,9,9};
	LNode *p = creat(a,sizeof(a) / sizeof(a[0]));
	traverse(p);
	deletedup(&p);
	traverse(p);
	return 0;
}
