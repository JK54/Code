#include <iostream>

struct LNode
{
	int key;
	LNode *next;
	explicit LNode(int x):key(x),next(nullptr){}
};

LNode* Kthtail(LNode *head,int k)
{
	if(k == 0 || head == nullptr)
		return nullptr;
	LNode *gofirst,*gosecond;
	int pa;
	gofirst = gosecond = head;
	for(pa = 0;gofirst != nullptr && pa <= k - 1;pa++)
		gofirst = gofirst->next;
	if(gofirst == nullptr)
	{
		if(pa < k - 1)
			return nullptr;
		else
			return gosecond;
	}
	while(gofirst != nullptr)
	{
		gofirst = gofirst->next;
		gosecond = gosecond->next;
	}
	return gosecond;
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int size = sizeof(a) / sizeof(a[0]);
	LNode *head = new LNode(a[0]);
	LNode *pre = head;
	for(int i = 1;i < size;i++)
	{
		LNode *tmp = new LNode(a[i]);
		pre->next = tmp;
		pre = tmp;
	}
	for(int i = 1;i <= size;i++)
	{
		pre = Kthtail(head,i);
		std::cout<<pre->key<<std::endl;
	}	
	for(int i = 0;i < size - 1;i++)
	{
		LNode *tmp = head->next;
		delete head;
		head = tmp;
	}
	return 0;
}
