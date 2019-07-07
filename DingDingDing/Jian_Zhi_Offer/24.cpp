#include <iostream>

struct LNode
{
	int key;
	LNode *next;
	explicit LNode(int x):key(x),next(nullptr){}
};

LNode *reverse(LNode *head)
{
	if(head == nullptr)
		return nullptr;
	if(head->next == nullptr)
		return head;
	LNode *pre,*cur,*nextp;
	pre = nullptr;
	cur = head;
	while(cur != nullptr)
	{
		nextp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = nextp;
	}
	return pre;
}

LNode *reverse2(LNode *head)
{
	if(head == nullptr)
		return nullptr;
	LNode *newhead = new LNode(0);
	LNode *nextp,*cur;
	cur = head;
	while(cur != nullptr)
	{
		nextp = cur->next;
		cur->next = newhead->next;
		newhead->next = cur;
		cur = nextp;
	}
	cur = newhead->next;
	delete newhead;
	return cur;
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	int size = sizeof(a) / sizeof(a[0]);
	LNode *head = new LNode(a[0]);
	LNode *pre = head;
	for(int i = 1;i < size;i++)
	{
		LNode *tmp = new LNode(a[i]);
		pre->next = tmp;
		pre = tmp;
	}
	
	head = reverse2(head);
	pre = head;
	while(pre != nullptr)
	{
		std::cout<<pre->key<<" ";
		pre = pre->next;
	}
	std::cout<<std::endl;

	head = reverse(head);
	pre = head;
	while(pre != nullptr)
	{
		std::cout<<pre->key<<" ";
		pre = pre->next;
	}
	std::cout<<std::endl;

	pre = head;
	while(pre != nullptr)
	{
		LNode *tmp = pre->next;
		delete pre;
		pre = tmp;
	}
	return 0;
}
