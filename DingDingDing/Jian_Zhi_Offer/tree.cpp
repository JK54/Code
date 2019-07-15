#include <iostream>
#include "tree.h"
#include <stack>
#include <queue>

Tree::Tree(int preo[],int ino[],int prelen,int inlen)
{
	if(prelen == 0|| inlen == 0 || prelen != inlen)
		root = nullptr;
	else
		root = CreateTreePreInOrder(preo,ino,prelen);
}	

Tree::~Tree()
{
	destroy(root);
}

void Tree::traverse()
{
	TraverseInOrder(root);
	std::cout<<std::endl;
}

bool Tree::issub(struct Tree &b)
{
	return Sub(root,b.root);
}

struct TreeNode* Tree::CreateTreePreInOrder(int preo[],int ino[],int len)
{
	if(len == 0)
		return nullptr;
	int posinorder = 0;
	while(posinorder < len && preo[0] != ino[posinorder])posinorder++;
	if(posinorder == len)
	{
		std::cout<<"invalid order"<<std::endl;
		return nullptr;
	}
	struct TreeNode *roo = new struct TreeNode(preo[0]);
	roo->lchild=CreateTreePreInOrder(preo + 1,ino,posinorder);
	roo->rchild=CreateTreePreInOrder(preo + posinorder + 1,ino + posinorder + 1,len - posinorder - 1);
	return roo;
}

void Tree::TraverseInOrder(struct TreeNode *p)
{
	if(p != nullptr)
	{
		TraverseInOrder(p->lchild);
		std::cout<<p->key<<" ";
		TraverseInOrder(p->rchild);
	}
}

void Tree::destroy(struct TreeNode *p)
{
	if(p != nullptr)
	{
		destroy(p->lchild);
		struct TreeNode *r = p->rchild;
		delete p;
		destroy(r);
	}
}

bool Tree::Sub(struct TreeNode *pa,struct TreeNode *pb)
{
	if(pb == nullptr)
		return true;
	if(pa != nullptr && pb != nullptr)
	{
		if(pa->key != pb->key)
			return Sub(pa->lchild,pb) || Sub(pa->rchild,pb);
		else
			return Sub(pa->lchild,pb->lchild) && Sub(pa->rchild,pb->rchild);
	}
	return false;
}

void Tree::reverse(TreeNode *p)
{
	if(p == nullptr)
		return ;
	TreeNode *tmp = p->lchild;
	p->lchild = p->rchild;
	p->rchild = tmp;
	reverse(p->lchild);
	reverse(p->rchild);
}

bool Tree::mirror(TreeNode *pa,TreeNode *pb)
{
	if(pa == nullptr && pb == nullptr)
		return true;
	if(pa == nullptr || pb == nullptr)
		return false;
	if(pa->key != pb->key)
		return false;
	return mirror(pa->lchild,pb->rchild) && mirror(pa->rchild,pb->lchild);
}

bool Tree::ismirror(Tree &b)
{
	return mirror(root,b.root);
}

struct QNode
{
	TreeNode *key;
	QNode *next;
	QNode(TreeNode *p):key(p),next(nullptr){}
};

void enqueue(TreeNode *p,QNode **head,QNode **tail)
{
	QNode *tmp = new QNode(p);
	if(*tail == nullptr)
		*tail = *head = tmp;
	else
	{
		(*tail)->next = tmp;
		*tail = tmp;
	}
}

TreeNode* dequeue(QNode **head,QNode **tail)
{
	if (*head == nullptr)
		return nullptr;
	TreeNode *p = (*head)->key;
	//防止递归析构
	(*head)->key = nullptr;
	QNode *tmp = (*head)->next;
	delete *head;
	*head = tmp;
	if(tmp == nullptr)
		*tail = nullptr;
	return p;
}

void Tree::traverselevel()
{
	QNode *head = nullptr,*tail = nullptr;
	enqueue(root,&head,&tail);
	while(head != nullptr)
	{
		TreeNode *trav = dequeue(&head,&tail);
		std::cout<<trav->key<<" ";
		if(trav->lchild != nullptr)
			enqueue(trav->lchild,&head,&tail);
		if(trav->rchild != nullptr)
			enqueue(trav->rchild,&head,&tail);
	}
	std::cout<<std::endl;
}

void Tree::traverselevelbylevel()
{
	QNode *head = nullptr,*tail = nullptr;
	int nextlevel,remain;
	enqueue(root,&head,&tail);
	nextlevel = 0;
	remain = 1;
	while(head != nullptr)
	{
		TreeNode *trav = dequeue(&head,&tail);
		std::cout<<trav->key<<" ";
		if(trav->lchild != nullptr)
		{
			enqueue(trav->lchild,&head,&tail);
			++nextlevel;	
		}
		if(trav->rchild != nullptr)
		{
			enqueue(trav->rchild,&head,&tail);
			++nextlevel;	
		}
		remain--;
		if(remain == 0)
		{
			std::cout<<std::endl;
			remain = nextlevel;
			nextlevel = 0;
		}
	}
	std::cout<<std::endl;
}

void Tree::traverselevelzigzag()
{
	std::stack<TreeNode*> left2right,right2left;
	int nextlevel,remain,zigzag;
	right2left.push(root);
	nextlevel = 0;
	remain = 1;
	zigzag = -1;
	while(!left2right.empty() || !right2left.empty())
	{
		TreeNode *trav;
		if(zigzag == 1)
		{
			trav = left2right.top();
			left2right.pop();
		}
		else
		{
			trav = right2left.top();
			right2left.pop();
		}
		std::cout<<trav->key<<" ";
		if(zigzag == -1)
		{
			if(trav->lchild != nullptr)
			{
				left2right.push(trav->lchild);
				nextlevel++;
			}
			if(trav->rchild != nullptr)
			{
				left2right.push(trav->rchild);
				nextlevel++;
			}
		}
		else
		{
			if(trav->rchild != nullptr)
			{
				right2left.push(trav->rchild);
				nextlevel++;
			}
			if(trav->lchild != nullptr)
			{
				right2left.push(trav->lchild);
				nextlevel++;
			}
		}		
		remain--;
		if(remain == 0)
		{
			remain = nextlevel;
			zigzag *= -1;
			nextlevel = 0;
			std::cout<<std::endl;
		}
	}
}

void Tree::TraversePostOrder()
{
	TreeNode *pre,*trav;
}
