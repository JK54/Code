#include <iostream>
#include "avltree.h"

size_t max(size_t a,size_t b)
{
	return a > b ? a : b;
}
void destroy(AVLTreeNode *roo)
{
	if(roo == nullptr)
		return;
	destroy(roo->lchild);
	destroy(roo->rchild);
	delete roo;
	roo = nullptr;
}

void TraverseInOrder(AVLTreeNode *roo)
{
	if(roo == nullptr)
		return;
	TraverseInOrder(roo->lchild);
	std::cout<<roo->data<<" ";
	TraverseInOrder(roo->rchild);
}

inline size_t Height(AVLTreeNode *roo)
{
	if(roo == nullptr)
		return 0;
	size_t lh = roo->lchild == nullptr ? 0 : roo->lchild->height;
	size_t lr = roo->rchild == nullptr ? 0 : roo->rchild->height;
	return max(lh,lr) + 1;
}


inline void UpdateHeight(AVLTreeNode *roo)
{
	if(roo != nullptr)
		roo->height = Height(roo);
}


bool Search(const int &vle,AVLTreeNode* root)
{
	AVLTreeNode *trav;
	trav = root;
	while(trav != nullptr)
	{
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			return true;
	}
	return false;
}


inline void setparent(AVLTreeNode *roo,AVLTreeNode *parent)
{
	if(roo != nullptr)
		roo->parent = parent;
}


AVLTreeNode* rotatel(AVLTreeNode *roo,AVLTreeNode *&root)
{
	AVLTreeNode *r;
	r = roo->rchild;
	replace_child(r,roo,roo->parent,root);
	roo->parent = r;
	roo->rchild = r->lchild;
	setparent(roo->rchild,roo);
	r->lchild = roo;
	UpdateHeight(roo);
	UpdateHeight(r);
	return r;
}

AVLTreeNode* rotater(AVLTreeNode *roo,AVLTreeNode *&root)
{
	AVLTreeNode *l;
	l = roo->lchild;
	replace_child(l,roo,roo->parent,root);
	roo->parent = l;
	roo->lchild = l->rchild;
	setparent(roo->lchild,roo);
	l->rchild = roo;
	UpdateHeight(roo);
	UpdateHeight(l);
	return l;
}


AVLTreeNode* rotatelr(AVLTreeNode *roo,AVLTreeNode *&root)
{
	AVLTreeNode *l,*lr;
	l = roo->lchild;
	lr = l->rchild;
	replace_child(lr,roo,roo->parent,root);
	l->parent = lr;
	l->rchild = lr->lchild;
	setparent(l->rchild,l);
	roo->parent = lr;
	roo->lchild = lr->rchild;
	setparent(roo->lchild,roo);
	lr->lchild = l;
	lr->rchild = roo;
	UpdateHeight(l);
	UpdateHeight(roo);
	UpdateHeight(lr);
	return lr;
}


AVLTreeNode* rotaterl(AVLTreeNode *roo,AVLTreeNode *&root)
{
	AVLTreeNode *r,*rl;
	r = roo->rchild;
	rl = r->lchild;
	replace_child(rl,roo,roo->parent,root);
	r->parent = rl;
	r->lchild = rl->rchild;
	setparent(r->lchild,r);
	roo->parent = rl;
	roo->rchild = rl->lchild;
	setparent(roo->rchild,roo);
	rl->rchild = r;
	rl->lchild = roo;
	UpdateHeight(r);
	UpdateHeight(roo);
	UpdateHeight(rl);
	return rl;
}


inline AVLTreeNode* fix_l(AVLTreeNode *roo,AVLTreeNode *&root)
{
	int lbf = Height(roo->lchild->rchild) - Height(roo->lchild->lchild);
	if(lbf == 1)
		return rotatelr(roo,root);
	else
		return rotater(roo,root);
}


inline AVLTreeNode* fix_r(AVLTreeNode *roo,AVLTreeNode *&root)
{
	int rbf = Height(roo->rchild->rchild) - Height(roo->rchild->lchild);
	if(rbf == -1)
		return rotaterl(roo,root);
	else
		return rotatel(roo,root);
}

void rebalance(AVLTreeNode *roo,AVLTreeNode *&root)
{
	size_t lh,rh,height;
	int bf;
	while(roo != nullptr)
	{
		height = Height(roo);
		lh = Height(roo->lchild);
		rh = Height(roo->rchild);
		bf = rh - lh;
		if(height != roo->height)
			UpdateHeight(roo);
		else if(bf >= -1 && bf <= 1)
			break;
		if(bf == -2)
			roo = fix_l(roo,root);
		else if(bf == 2)
			roo = fix_r(roo,root);
		roo = roo->parent;
	}
}

bool Insert(const int &vle,AVLTreeNode *&root)
{
	AVLTreeNode *pre,*trav;
	pre = nullptr;
	trav = root;
	while(trav != nullptr)
	{
		pre = trav;
		if(trav->data >vle)	
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
			return false;
	}
	trav = new AVLTreeNode(vle);
	trav->parent = pre;
	if(pre == nullptr)
		root = trav;
	else
	{
		if(pre->data > vle)
			pre->lchild = trav;
		else
			pre->rchild = trav;
		rebalance(pre,root);
	}
	return true;
}


inline void replace_child(AVLTreeNode *n,AVLTreeNode *o,AVLTreeNode *p,AVLTreeNode *&root)
{
	if(p != nullptr)
	{
		if(p->lchild == o)
			p->lchild = n;
		else
			p->rchild = n;
		if(n != nullptr)
			n->parent = p;
	}
	else
	{
		root = n;
		setparent(n,nullptr);
	}
}

bool Remove(const int &vle,AVLTreeNode *&root)
{
	AVLTreeNode *trav,*pre,*parent;
	trav = root;
	while(trav != nullptr)
	{
		if(trav->data == vle)
			break;
		else if(trav->data > vle)
			trav = trav->lchild;
		else
			trav = trav->rchild;
	}
	if(trav == nullptr)
		return false;
	pre = trav;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	{
		trav = trav->lchild;
		while(trav->rchild != nullptr)
			trav = trav->rchild;
		pre->data = trav->data;
		pre = trav;
	}
	if(trav->lchild != nullptr)
		trav = trav->lchild;
	else
		trav = trav->rchild;
	parent = pre->parent;
	replace_child(trav,pre,parent,root);
	delete pre;
	if(parent != nullptr)
		rebalance(parent,root);
	return true;
}	
