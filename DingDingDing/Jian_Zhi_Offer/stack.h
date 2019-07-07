#include <limits.h>

typedef struct SNode
{
	int key;
	struct SNode *next;
} SNode;

struct Stack
{
	SNode *top,*mtop;
	int min2s;

	Stack():top(nullptr),mtop(nullptr),min2s(INT_MAX){}
	~Stack();
	SNode* push(int x);
	int pop();
	int min();
	int topelement();
	bool poplist(int a[],int b[],int len);
};
