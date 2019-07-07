
struct ListNode
{
	int m_nValue;
	struct ListNode *m_pNext;
};

struct ListNode* create(int data[],int n);
void traverse(struct ListNode *p);
void destroy(struct ListNode *p);
