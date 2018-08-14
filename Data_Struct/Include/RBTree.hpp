#ifndef _RBTREE_H
#define _RBTREE_H

#include "sys_comm.h"
#include "Stack.hpp"
#define RB_RED 0
#define RB_BLACK 1

//BSTree naturally use inorder as the  order.
//Read from wiki.Important properties are as below.

//properties(judged by IsRBT()):
//1) A node is either red or black
//2) The root is black
//3) All leaves (NULL) are black
//4) Both children of every red node are black
//5) Every simple path from root to leaves contains the same number of black nodes.

//Insert Case:
//1) Newnode is the first node,or the color of root is changed to red,just paint it black.
//2) Parent of newnode is black,then drop the rebalance as it already balanced.
//3) If newnode has a red uncle and red parent,then draw them black,and draw the grandparent red,trace back until root or case 5.
//4) Pre-work for case 5.newnode has a red parent((of course),and owns a black uncle or a empty uncle,rotate the newnode in a straight line with grandparent.
//5) rotate from grandparent.change color.Whether the new parent of newnode is red or not,the rebalance prcedure is done,ignore it.

//Delete Case
template<typename T>
struct RBTreeNode
{
	RBTreeNode():lchild(nullptr),rchild(nullptr),parent(nullptr){};
	RBTreeNode(T x):data(x),color(RB_RED),lchild(nullptr),rchild(nullptr),parent(nullptr){};
	RBTreeNode(T x,bool cl):data(x),color(cl),lchild(nullptr),rchild(nullptr),parent(nullptr){};
	T data;
	bool color;
	RBTreeNode *lchild,*rchild,*parent;
};

template <typename T>
class RBTree
{
	public:
		RBTree():root(nullptr),count(0){};
		RBTree(T x):root(new RBTreeNode<T>(x,RB_BLACK)),count(1){};
		~RBTree();
		void CreatTree(T *data,const int &n);
		void CreatTree(std::istream &is);
		bool IsRBT();
		void Traverse();
		bool Search(const T &vle);
		bool Insert(const T &vle);
		bool Remove(const T &vle);
		RBTreeNode<T> *Root(){return root;};
		void PrintCount(){std::cout<<count<<std::endl;};
	private:
		RBTreeNode<T>* first();
		RBTreeNode<T>* last();
		RBTreeNode<T>* pre(RBTreeNode<T> *roo);
		RBTreeNode<T>* next(RBTreeNode<T> *roo);
		RBTreeNode<T>* grandparent(RBTreeNode<T> *roo);
		RBTreeNode<T>* uncle(RBTreeNode<T> *roo);
		inline RBTreeNode<T>* brother(RBTreeNode<T> *roo,RBTreeNode<T> *parent);
		size_t blacklength(RBTreeNode<T> *roo);
		inline bool redparent(RBTreeNode<T> *roo);
		//replace() relink all the relation from pre to trav,replace2() just copy the data from trav to pre.
		void replace(RBTreeNode<T> *trav,RBTreeNode<T> *pre);
		// void replace2(RBTreeNode<T> *trav,RBTreeNode<T> *pre);
		void rotatel(RBTreeNode<T> *roo);
		void rotater(RBTreeNode<T> *roo);
		inline bool getcolor(RBTreeNode<T> *roo);
		void destroy(RBTreeNode<T> *roo);
		//-------member-----------
		RBTreeNode<T> *root;
		int count;
};

template<typename T>
void RBTree<T>::destroy(RBTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	if(roo->lchild != nullptr)
		destroy(roo->lchild);
	if(roo->rchild != nullptr)
		destroy(roo->rchild);
	delete roo;
	roo = nullptr;
}

template<typename T>
RBTree<T>::~RBTree<T>()
{
	destroy(root);
	root = nullptr;
}

template<typename T>
bool RBTree<T>::IsRBT()
{
	//property 1 : a node is either red or black.
	RBTreeNode<T> *trav = root;
	Stack<int> len;
	Stack<RBTreeNode<T>*> path;
	int *blacklength = new int [count];
	int num = 0,length = 0;
	bool endmark = false,result = true;
	if(trav == nullptr)
		endmark =  true;
	//property 2 : root is black
	if(endmark == false && root->color == RB_RED)
		endmark = true,result = false;
	while(endmark == false && (!path.IsEmpty() || trav != nullptr))
	{
		while(trav != nullptr)
		{
			if(trav->color == RB_BLACK)
				length++;
			len.Push(length);
			path.Push(trav);
			trav = trav->lchild;
		}
		if(!path.IsEmpty())
		{
			path.Pop(trav);
			len.Pop(length);
			//property 3 : all leave are black.
			if(trav->lchild == nullptr || trav->rchild == nullptr)
			{
				blacklength[num++] = length + 1;
				//property 5 : every simple path has the same number of black nodes.
				if(blacklength[num - 1] != blacklength[0])
					endmark = true,result = false;
			}
			//property 4:both children of red nodes are blacks.
			if(trav->lchild != nullptr && trav->lchild->color == RB_RED && trav->color == RB_RED)
				endmark = true,result = false;
			if(trav->lchild != nullptr && trav->lchild->color == RB_RED && trav->color == RB_RED)
				endmark = true,result = false;
			trav = trav->rchild;
		}
	}
	delete [] blacklength;
	return result;
}
template<typename T>
RBTreeNode<T>* RBTree<T>::grandparent(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *gp;
	if(roo == root || roo == nullptr)
		gp = nullptr;
	else
		gp = roo->parent->parent;
	return gp;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::uncle(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *gp,*uncle;
	gp = grandparent(roo);
	if(gp != nullptr)
	{
		if(gp->rchild == roo->parent)
			uncle = gp->lchild;
		else
			uncle = gp->rchild;
	}
	else
		uncle = nullptr;
	return uncle;
}

template<typename T>
inline RBTreeNode<T>* RBTree<T>::brother(RBTreeNode<T> *roo,RBTreeNode<T> *parent)
{
	return roo == root ? nullptr : parent->lchild == roo ? parent->rchild : parent->lchild;
}

template<typename T>
size_t RBTree<T>::blacklength(RBTreeNode<T> *roo)
{
	size_t height = 0;
	if(roo->lchild == nullptr || roo->rchild == nullptr)
		height++;
	while(roo->parent != nullptr)
		if(roo->color == RB_BLACK)
			height++;
	return height;
}
template<typename T>
RBTreeNode<T>* RBTree<T>::first()
{
	RBTreeNode<T> *roo;
	roo = root;
	while(roo->lchild != nullptr)
		roo = roo->lchild;
	return roo;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::last()
{
	RBTreeNode<T> *roo;
	roo = root;
	while(roo->rchild != nullptr)
		roo = roo->rchild;
	return roo;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::pre(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *trav;
	trav = roo;
	if(trav->lchild != nullptr)
	{
		trav = trav->lchild;
		while(trav->rchild != nullptr)
			trav = trav->rchild;
	}
	else
	{
		while(trav != root && trav == trav->parent->lchild)
			trav = trav->parent;
		trav = trav->parent;
	}
	return trav;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::next(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *trav;
	trav = roo;
	if(trav->rchild != nullptr)
	{
		trav = trav->rchild;
		while(trav->lchild != nullptr)
			trav = trav->lchild;
	}
	else
	{
		while(trav != root && trav == trav->parent->rchild)
			trav = trav->parent;
		trav = trav->parent;
	}
	return trav;
}

template<typename T>
void RBTree<T>::replace(RBTreeNode<T> *trav,RBTreeNode<T> *pre)
{
	if(trav != nullptr)
	{
		if(trav != pre->lchild)
			trav->lchild = pre->lchild;
		if(trav != pre->rchild)
			trav->rchild = pre->rchild;
		trav->parent = pre->parent;
		//trav->color = pre->color;
		if(trav->lchild != nullptr)
			trav->lchild->parent = trav;
		if(trav->rchild != nullptr)
			trav->rchild->parent = trav;
	}
	if(pre->parent != nullptr)
	{
		if(pre->parent->lchild == pre)
			pre->parent->lchild = trav;
		else
			pre->parent->rchild = trav;
	}
	else
		root = trav;
	delete pre;
	pre = nullptr;
}

template<typename T>
void RBTree<T>::rotatel(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *n,*rn,*rln;
	n = roo;
	rn = n->rchild;
	rln = rn->lchild;
	rn->lchild = n;
	rn->parent = n->parent;
	if(n != root)
	{
		if(n->parent->lchild == n)
			n->parent->lchild = rn;
		else
			n->parent->rchild = rn;
	}
	else
		root = rn;
	n->parent = rn;
	n->rchild = rln;
	if(rln != nullptr)
		rln->parent = n;
}

template<typename T>
void RBTree<T>::rotater(RBTreeNode<T> *roo)
{
	RBTreeNode<T> *n,*ln,*lrn;
	n = roo;
	ln = n->lchild;
	lrn = ln->rchild;
	ln->rchild = n;
	ln->parent = n->parent;
	if(n != root)
	{
		if(n->parent->lchild == n)
			n->parent->lchild = ln;
		else
			n->parent->rchild = ln;
	}
	else
		root = ln;
	n->parent = ln;
	n->lchild = lrn;
	if(lrn != nullptr)
		lrn->parent = n;
}

template<typename T>
void RBTree<T>::Traverse()
{
	RBTreeNode<T> *trav = first();
	while(trav != nullptr)
	{
		std::cout<<trav->data<<" ";
		trav = next(trav);
	}
	std::cout<<std::endl;
}

template<typename T>
bool RBTree<T>::Search(const T &vle)
{
	RBTreeNode<T> *trav = root;
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

template<typename T>
inline bool RBTree<T>::redparent(RBTreeNode<T> *roo)
{
	if(roo != root && roo->parent->color == RB_RED)
		return true;
	else
		return false;
}

//caseN logic
template<typename T>
bool RBTree<T>::Insert(const T &vle)
{
	RBTreeNode<T> *trav,*p,*u,*g;
	trav = root;
	p = nullptr;
	//find the position to insert,like the bst
	while(trav != nullptr)
	{
		p = trav;
		if(trav->data > vle)
			trav = trav->lchild;
		else if(trav->data < vle)
			trav = trav->rchild;
		else
		{
			std::cout<<"repeating elements"<<std::endl;
			return false;
		}
	}
	trav = new RBTreeNode<T>(vle);
	count++;
	//if trav is the first node of rbtree.
	if(p == nullptr)
	{
		root = trav;
		root->color = RB_BLACK;
		return true;
	}
	if(p->data > vle)
		p->lchild = trav;
	else
		p->rchild = trav;
	trav->parent = p;
	//the redparent() implicits case 2.red node must has parent,so if a node's parent is red,then it must own a grandparent.
	for(g = grandparent(trav),u = uncle(trav);redparent(trav);g = grandparent(trav),p = trav->parent,u = uncle(trav))
	{
		//case 3:unclde and parent are both red.
		if(u != nullptr && u->color == RB_RED)
		{
			g->color = RB_RED;
			p->color = RB_BLACK;
			u->color = RB_BLACK;
			trav = g;
			continue;
		}
		//the if-else statement handle the mirror situation,atually the same logic.after case 5,the tree recover balance.
		else
		{
			if(p == g->lchild)
			{
				//case 4 : pre-hadle for case 5,to make sure trav is the lchild of parent.
				if(trav == p->rchild)
				{
					//after the rotate,p become the child of trav,we need to ascend to the former layer.because we need to change the color of node in the "parent" position.
					rotatel(p);
					p = p->parent;
				}
				//case 5.
				rotater(g);
			}
			//p == g->rchild
			else
			{
				if(trav == p->lchild)
				{
					rotater(p);
					p = p->parent;
				}
				rotatel(g);
			}
			g->color = RB_RED;
			p->color = RB_BLACK;
			//once case5,the rablance is done.
			break;
		}
	}
	//case 1:root is black.
	root->color = RB_BLACK;
	return true;
}

template<typename T>
inline bool RBTree<T>::getcolor(RBTreeNode<T> *roo)
{
	if(roo != nullptr)
		return roo->color;
	return RB_BLACK;
}

template<typename T>
bool RBTree<T>::Remove(const T &vle)
{
	//g for grandparent,p for parent,u for uncle,b for brother.
	RBTreeNode<T> *p,*b,*trav,*tmp;
	bool tcolor,pcolor,bcolor,lbcolor,rbcolor;
	trav = root;
	//find position
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
	count--;
	//find the alternative node,define that p point to wanted,trav ponit to the alternate.
	p = trav;
	//tranfer the full-child situation to the common situation,one non-null child at most.
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	{
		//seek from rchild-subtree.
		trav = next(p);
		p->data = trav->data;
		p = trav;
	}
	if(trav->lchild != nullptr)
		trav = trav->lchild;
	//trav may be nullptr in the else-statement.
	else
		trav = trav->rchild;
	pcolor = p->color;
	if(trav == nullptr && p != root)
		tmp = p->parent;
	else
		tmp = trav;
	replace(trav,p);
	//simple situation:
	//1.the wanted is red
	//2.the wanted is black,the child is red 
	if(pcolor == RB_RED)
		return true;
	else if(pcolor == RB_BLACK && getcolor(trav) == RB_RED)
	{
		trav->color = RB_BLACK;
		return true;
	}
	//both the wanted and child is black,disscussed in 6 cases.
	else
	{	
		if(trav == nullptr)
			p = tmp;
		else
			p = trav->parent;
		//case 1:trav become root.
		if(trav == root)
			return true;
		while(trav != root)
		{
			b = brother(trav,p);
			pcolor = getcolor(p),bcolor = getcolor(b),lbcolor = getcolor(b->lchild),rbcolor = getcolor(b->rchild);
			//case 3,b and lchild,rchild of b all are black.
			// use getcolor in case of null node of child of b,considering the balance defition,b can not be empty.	
			if(pcolor == RB_BLACK && bcolor == RB_BLACK && lbcolor == RB_BLACK && rbcolor == RB_BLACK)
			{
				b->color = RB_RED;
				if(trav != nullptr)
					trav = trav->parent;
				else
					trav = p;
				p = trav->parent;
				continue;
			}
			//case 2.the lchild,rchild of s must exist.because red node must have a black parent and black children.
			if(bcolor == RB_RED)
			{
				if(trav == p->lchild)
					rotatel(p);
				else
					rotater(p);
				p->color = RB_RED;
				b->color = RB_BLACK;
				b = brother(trav,p);
				bcolor = getcolor(b),lbcolor = getcolor(b->lchild),rbcolor = getcolor(b->rchild);
			}
			//case 4:
			if(pcolor == RB_RED && bcolor == RB_BLACK && lbcolor == RB_BLACK && rbcolor == RB_BLACK)
			{
				p->color = RB_BLACK;
				b->color = RB_RED;
				break;
			}
			//case 5.pre-work for case 6.
			if(bcolor == RB_BLACK)
			{
				if(trav == p->lchild && lbcolor == RB_RED && rbcolor == RB_BLACK)
				{
					b->color = RB_RED;
					b->lchild->color = RB_BLACK;
					rotater(b);
					b = brother(trav,p);
					rbcolor = RB_RED;
				}
				else if(trav == p->rchild && lbcolor == RB_BLACK && rbcolor == RB_RED)
				{
					b->color = RB_RED;
					b->rchild->color = RB_BLACK;
					rotatel(b);
					b = brother(trav,p);
					lbcolor = RB_RED;
				}
			}
			//case 6
			if(rbcolor == RB_RED || lbcolor == RB_RED)
			{
				b->color = p->color;
				p->color = RB_BLACK;
				if(trav == p->lchild)
				{
					rotatel(p);
					b->rchild->color = RB_BLACK;
				}
				else
				{
					rotater(p);
					b->lchild->color = RB_BLACK;
				}
				break;
			}
		}
	}
	return true;
}
#endif
