#include <iostream>
#include <fstream>
#include <random>
struct ComplexListNode
{
	int key;
	ComplexListNode *next;
	ComplexListNode *sibling;
	explicit ComplexListNode(int x):key(x),next(nullptr),sibling(nullptr){}
};

void destroy(ComplexListNode *p)
{
	ComplexListNode *tmp;
	while(p != nullptr)
	{
		tmp = p->next;
		delete p;
		p = tmp;
	}
}

void clone_next(ComplexListNode *head)
{
	if(head == nullptr)
		return;
	ComplexListNode *trav = head;
	while(trav != nullptr)
	{
		ComplexListNode *tmp = new ComplexListNode(trav->key);
		tmp->next = trav->next;
		trav->next = tmp;
		trav = tmp->next;
	}
}

void clone_sibling(ComplexListNode *head)
{
	if(head == nullptr)
		return;
	ComplexListNode *ori = head;
	ComplexListNode *clone = ori->next;
	while(clone != nullptr)
	{
		if(ori->sibling == nullptr)
			clone->sibling = ori->sibling;
		else
			clone->sibling = ori->sibling->next;
		ori = clone->next;
		if(ori != nullptr)
			clone = ori->next;
		else
			clone = nullptr;
	}
}

ComplexListNode *depart(ComplexListNode *head)
{
	if(head == nullptr)
		return nullptr;
	ComplexListNode *ori,*clone,*clonehead;
	
	ori = head;
	clonehead = ori->next;
	clone =  clonehead;
	while(clone != nullptr)
	{
		ori->next = clone->next;
		ori = ori->next;
		if(ori != nullptr)
			clone->next = ori->next;
		clone = clone->next;
	}
	return clonehead;
}

ComplexListNode* create(int a[],int n)
{
	if(a == nullptr || n <= 0)
		return nullptr;
	ComplexListNode *head,*trav,*tmp;
	std::random_device ss;
	std::mt19937 mt(ss());
	head = new ComplexListNode(a[0]);
	trav = head;
	for(int i = 1;i < n;i++)
	{
		tmp = new ComplexListNode(a[i]);
		tmp->next = trav->next;
		trav->next = tmp;
		trav = tmp;
	}
	trav = head;
	while(trav != nullptr)
	{
		unsigned int i;
		i = mt();
		std::cout<<"rand : " <<i<<std::endl;
		i %= n;
		if(i != 0)
			tmp = head;
		else
			tmp = nullptr;
		for(int j = 0;j < i;j++)
			tmp = tmp->next;
		trav->sibling = tmp;
		trav = trav->next;
	}
	return head;
}

void traverse(ComplexListNode *p)
{
	while(p != nullptr)
	{
		std::cout<<p->key<<" ";
		p = p->next;
	}
	std::cout<<std::endl;
}

void viewsib(ComplexListNode *p)
{
	int i = 0;
	while(p != nullptr && i++ < 15)
	{
		std::cout<<p->key<<" ";
		p = p->sibling;
	}
	std::cout<<std::endl;
}

ComplexListNode* clone(ComplexListNode *p)
{
	clone_next(p);
	clone_sibling(p);
	ComplexListNode *clone = depart(p);
	destroy(p);
	return clone;
}


int main()
{
	int a[] = {1,2,3,4,5,6,7};
	int size = sizeof(a) / sizeof(a[0]);
	ComplexListNode *p = create(a,size);
	traverse(p);
	viewsib(p);
	ComplexListNode *c = clone(p);
	traverse(c);
	viewsib(c);
	destroy(c);
	return 0;
}
