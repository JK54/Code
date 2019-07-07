#include <iostream>

struct LNode
{
	int key;
	LNode *next;
	explicit LNode(int x):key(x),next(nullptr){}
};

LNode* circle(LNode *head)
{
	if(head == nullptr)
		return nullptr;
	LNode *fast,*slow;
	slow = head;
	fast = head->next;
	while(fast != nullptr && fast != slow)
	{
		for(int i = 0;fast->next != nullptr && i < 2;i++)
			fast = fast->next;
		slow = slow->next;
	}
	return fast;
}

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	LNode *head = new LNode(a[0]);
	LNode *gate,*pre = head,*p;
	int len;
	for(int i = 1;i < 10;i++)
	{
		LNode *tmp = new LNode(a[i]);
		pre->next = tmp;
		pre = tmp;
		if(i == 3)
			gate = pre;
	}
	pre->next = gate;

	p = circle(head);
	if(p == nullptr)
	{
		std::cout<<"not a circle";
		return -1;
	}
	std::cout<<"circle at "<<p->key<<std::endl;

	pre = p;
	p = p->next;
	len = 1;
	while(pre != p)
	{
		p = p->next;
		len++;
	}
	std::cout<<len<<std::endl;
	p = pre = head;
	for(int i = 0;i < len;i++)
		pre = pre->next;

	while(pre != p)
	{
		pre = pre->next;
		p = p->next;
	}
	std::cout<<"dingding:"<<p->key<<std::endl;
	

	pre = head;
	for(int i = 0;i < 20;i++)
	{
		std::cout<<pre->key<<std::endl;
		pre = pre->next;
	}
	pre = head;
	for(int i = 0;i < 10;i++)
	{
		LNode *tmp = pre->next;
		delete pre;
		pre = nullptr;
		pre = tmp;
	}
}
