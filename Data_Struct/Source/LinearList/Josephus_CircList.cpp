#include <iostream>

struct CircList
{
	int data;
	CircList *next;
};

void Josephus(CircList *head,int s,int m,int n)
{
	CircList *p;
	CircList *pr = head;
	head->data = 1;
	pr->next = pr;
	for(int i = 2;i <= n;++i)
	{
		p = new CircList;
		p->data = i;
		p->next = pr->next;
		pr->next = p;
		pr = p;
	}
	p = head;
	for(int i = 1;i < s;++i)
		p = p->next;
	while(n > 0)
	{
		for(int i = 1;i < m ;i++)
		{ 	
			pr = p;
			p = p->next;
		}
		std::cout<<p->data<<" ";
		pr->next = p->next;
		delete p;
		p = pr->next;
		n--;
	}
}

/* int main() */
// {
	// CircList *a = new CircList;
	// int s = 1,m = 5,n = 9;
	// Josephus(a,s,m,n);
/* } */
