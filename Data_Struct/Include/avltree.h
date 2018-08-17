#ifndef _AVLTree_H
#define _AVLTree_H

#include <iostream>

class AVLTreeNode
{
	public:
	AVLTreeNode():height(1),parent(this),lchild(nullptr),rchild(nullptr){}
	AVLTreeNode(int x):data(x),height(1),parent(this),lchild(nullptr),rchild(nullptr){}
	int data;
	size_t height;
	AVLTreeNode *parent;
	AVLTreeNode *lchild;
	AVLTreeNode *rchild;
};

bool Insert(const int &vle,AVLTreeNode *&root);
bool Remove(const int &vle,AVLTreeNode *&root);
bool Search(const int &vle,AVLTreeNode *root);
void TraverseInOrder(AVLTreeNode *roo);
void UpdateHeight(AVLTreeNode *roo);
void rebalance(AVLTreeNode *roo,AVLTreeNode *&root);
void replace_child(AVLTreeNode*,AVLTreeNode*,AVLTreeNode*,AVLTreeNode *&root);
size_t Height(AVLTreeNode *roo);
void setparent(AVLTreeNode *,AVLTreeNode *);
AVLTreeNode* fix_l(AVLTreeNode *roo,AVLTreeNode *&root);
AVLTreeNode* fix_r(AVLTreeNode *roo,AVLTreeNode *&root);
size_t max(size_t a,size_t b);
AVLTreeNode* rotatel(AVLTreeNode *roo,AVLTreeNode *&root);
AVLTreeNode* rotater(AVLTreeNode *roo,AVLTreeNode *&root);
AVLTreeNode* rotatelr(AVLTreeNode *roo,AVLTreeNode *&root);
AVLTreeNode* rotaterl(AVLTreeNode *roo,AVLTreeNode *&root);
void destroy(AVLTreeNode *roo);

#endif
