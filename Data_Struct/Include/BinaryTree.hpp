#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "sys_comm.h"
#include "Stack.hpp"
#include "Queue.hpp"

template<typename T>
class BinTreeNode;

template<typename T>
class BinTree;

template<typename T>
class ThreadNode;

template<typename T>
class ThreadTree;

template<typename T>
BinTreeNode<T>* CreateTreeByInPostOrder(T*,T*,int);

template<typename T>
BinTreeNode<T>* CreateTreeByPreInOrder(T*,T*,int);

template<typename T>
std::set<BinTreeNode<T>*> CreateTreeByInPostOrder_Duplicated(T*,T*,int);

template<typename T>
class BinTreeNode
{
	friend class BinTree<T>;
	friend class ThreadNode<T>;
	friend class ThreadTree<T>;
	friend BinTreeNode<T>* CreateTreeByPreInOrder<T>(T *preo,T *ino,int n);
	friend BinTreeNode<T>* CreateTreeByInPostOrder<T>(T *ino,T *posto,int n);
	T data;
	BinTreeNode<T> *lchild;
	BinTreeNode<T> *rchild;
	BinTreeNode():lchild(nullptr),rchild(nullptr){}
	BinTreeNode(T x):data(x),lchild(nullptr),rchild(nullptr){}
};

template<typename T>
class BinTree
{
	//reconsider the situation:there are some nodes have the same value.
	//In some case,replicated elements can build mutiple binarytree.
	//e.g:inorder:2111211,postorder:2121111,it can be 1( 2 1( 1( 1 2) 1) or 1( 1(2) 1(1(2 1)))
	//Maybe there is a algorithm to build all cases of trees,remains to be solved.
	friend BinTreeNode<T>* CreateTreeByPreInOrder<T>(T *preo,T *ino,int n);
	friend BinTreeNode<T>* CreateTreeByInPostOrder<T>(T *ino,T *posto,int n);
	friend std::set<BinTreeNode<T>*> CreateTreeByInPostOrder_Duplicated<T>(T *ino,T *posto,int n);//no definition.
	public:
	static T endm;

	BinTree();
	BinTree(T x);
	~BinTree();
	BinTree(const BinTree<T> &s);

	bool operator==(const BinTree<T> &s);
	bool operator!=(const BinTree<T> &s);//in fact,the opposite value of "==".
	BinTree<T>& operator=(const BinTree<T> &s);

	//get root node and modify endmark
	BinTreeNode<T>* Root(){return root;}
	void SetMark(T x){endm = x;}
	void CreateTreePreOrder(BinTreeNode<T> *&ro,std::istream &is);
	//recursive traverse
	//bool type variable "ingen" control the output in genlist format(1) or not(0)
	void TraversePreOrder(BinTreeNode<T> *ro,bool ingen);
	void TraverseInOrder(BinTreeNode<T> *ro);
	void TraversePostOrder(BinTreeNode<T> *ro);
	//no-recursive traverse
	void TraversePreOrder_NR1(BinTreeNode<T> *roo);
	void TraversePreOrder_NR2(BinTreeNode<T> *roo);
	void TraversePreOrder_NR3(BinTreeNode<T> *roo);
	void TraverseInOrder_NR(BinTreeNode<T> *roo);
	void TraversePostOrder_NR(BinTreeNode<T> *roo);
	void TraverseLevelOrder(BinTreeNode<T> *roo);

	//use traverse to complete
	size_t Height(BinTreeNode<T> *roo);
	size_t Size();
	BinTreeNode<T>* Copy(BinTreeNode<T> *orign);
	bool Equal(BinTreeNode<T> *l,BinTreeNode<T> *r);

	private:
	BinTreeNode<T> *root;
	size_t *use;//the binary tree use count,control the distructor.
	void destroy(BinTreeNode<T> *ro);
};


template<typename T>
T BinTree<T>::endm;

	template<typename T>
BinTree<T>::BinTree()
{
	root = new BinTreeNode<T>;
	use = new size_t(1);
}

	template<typename T>
BinTree<T>::BinTree(T x)
{
	root = new BinTreeNode<T>(x);
	use = new size_t(1);
}

	template<typename T>
void BinTree<T>::destroy(BinTreeNode<T> *root)
{
	if(root == nullptr)
		return;
	else
	{
		destroy(root->lchild);
		destroy(root->rchild);
		delete root;
		root = nullptr;
	}
}

	template<typename T>
BinTree<T>::~BinTree()
{
	if(--*use == 0)
	{
		// std::cout<<"no longer used,destroy it"<<std::endl;
		destroy(root);
		delete use;
	}
}

	template<typename T>
void BinTree<T>::CreateTreePreOrder(BinTreeNode<T> *&ro,std::istream &is)
{
	T x;
	is>>x;
	if(x == BinTree<T>::endm)
	{
		return;
	}
	else
	{
		if(ro == nullptr)
		{
			BinTreeNode<T> *tmp = ro;
			ro = new BinTreeNode<T>(x);
			delete tmp;
			tmp = nullptr;
		}
		else
			ro->data = x;
		CreateTreePreOrder(ro->lchild,is);
		CreateTreePreOrder(ro->rchild,is);
	}
}

	template<typename T>
BinTreeNode<T>* CreateTreeByPreInOrder(T *preo,T *ino,int n)
{
	if(n == 0)
		return nullptr;
	int k = 0;
	while(preo[0] != ino[k])k++;
	BinTreeNode<T> *t = new BinTreeNode<T>(preo[0]);
	t->lchild = CreateTreeByPreInOrder(preo + 1,ino,k);
	t->rchild = CreateTreeByPreInOrder(preo + k + 1,ino + k + 1,n - k - 1 );
	return t;
}

	template<typename T>
BinTreeNode<T>* CreateTreeByInPostOrder(T *ino,T *posto,int n)
{
	if(n == 0)
		return nullptr;
	int k = 0 ;
	while(posto[n - 1] != ino[k])k++;
	BinTreeNode<T> *p = new BinTreeNode<T>(posto[n - 1]);
	p->lchild = CreateTreeByInPostOrder(ino,posto,k);
	p->rchild = CreateTreeByInPostOrder(ino + k + 1,posto + k,n - k - 1);
	return p;
}

	template<typename T>
void BinTree<T>::TraversePreOrder(BinTreeNode<T> *ro,bool ingen)
{
	if(ingen == false)
	{
		if(ro == nullptr)
		{
			return;
		}
		else
		{
			std::cout<<ro->data<<" ";
			TraversePreOrder(ro->lchild,ingen);
			TraversePreOrder(ro->rchild,ingen);
			return;
		}
	}
	else
	{
		if(ro == nullptr)
		{
			return;
		}
		else
		{
			std::cout<<ro->data<<" ( ";
			TraversePreOrder(ro->lchild,ingen);
			TraversePreOrder(ro->rchild,ingen);
			std::cout<<" ) ";
			return;
		}

	}
}

	template<typename T>
void BinTree<T>::TraverseInOrder(BinTreeNode<T> *ro)
{
	if(ro == nullptr)
	{
		return;
	}
	else
	{
		TraverseInOrder(ro->lchild);
		std::cout<<ro->data<<" ";
		TraverseInOrder(ro->rchild);
		return;
	}
}

	template<typename T>
void BinTree<T>::TraversePostOrder(BinTreeNode<T> *ro)
{
	if(ro == nullptr)
	{
		return;
	}
	else
	{
		TraversePostOrder(ro->lchild);
		TraversePostOrder(ro->rchild);
		std::cout<<ro->data<<" ";
		return;
	}
}


//set xmark as flag of null lchild.if lchild is not nullptr,then output it,else pop the brother rchild.
//It's very similar to NR2,but it need a extra parameters to store the last pop operation is successed or not.It take one more bit memory space,and NR2 take more time.When it come to a extra large tree,NR1 could have better performance.
	template<typename T>
void BinTree<T>::TraversePreOrder_NR1(BinTreeNode<T> *roo)
{
	Stack<BinTreeNode<T>*> s;
	bool xmark = true;
	BinTreeNode<T> *trav = roo;
	while(trav != nullptr&& xmark)
	{
		std::cout<<trav->data<<" ";
		if(trav->rchild != nullptr)
			s.Push(trav->rchild);
		if(trav->lchild != nullptr)
			trav = trav->lchild;
		else
			xmark = s.Pop(trav);
	}
}

	template<typename T>
void BinTree<T>::TraversePreOrder_NR2(BinTreeNode<T> *roo)
{
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *trav = roo;
	while(trav != nullptr || !s.IsEmpty())
	{
		std::cout<<trav->data<<" ";
		if((trav->lchild == nullptr && trav->rchild == nullptr)&& s.IsEmpty())
			break;
		if(trav->rchild != nullptr)
			s.Push(trav->rchild);
		if(trav->lchild != nullptr)
			trav = trav->lchild;
		else
			s.Pop(trav);
	}
}

//diferent between NR2 and NR3:the count of push and pop operation of NR2 is more less than NR3,but NR2 need to do the extra step of if-operation each time the loop to make sure that when it come to the last node the loop could break,or it will never end.But I thought the performance of NR2 is still better than NR3.
	template<typename T>
void BinTree<T>::TraversePreOrder_NR3(BinTreeNode<T> *roo)
{
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *trav = roo;
	while(trav != nullptr || !s.IsEmpty())
	{
		if(trav != nullptr)
		{
			std::cout<<trav->data<<" ";
			s.Push(trav);
			trav = trav->lchild;
		}
		else
		{
			s.Pop(trav);
			trav = trav->rchild;
		}
	}
}

	template<typename T>
void BinTree<T>::TraverseInOrder_NR(BinTreeNode<T> *roo)
{
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *trav = roo;
	while(!s.IsEmpty() ||trav != nullptr)
	{
		while(trav != nullptr)
		{
			s.Push(trav);
			trav = trav->lchild;
		}
		if(!s.IsEmpty())
		{
			s.Pop(trav);
			std::cout<<trav->data<<" ";
			trav = trav->rchild;
		}
	}
}

	template<typename T>
void BinTree<T>::TraversePostOrder_NR(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *trav = roo;
	BinTreeNode<T> *pre = nullptr;
	while(trav != nullptr)
	{
		s.Push(trav);
		trav = trav->lchild;
	}
	while(s.Pop(trav))
	{
		if(trav->rchild == nullptr || trav->rchild == pre)
		{
			std::cout<<trav->data<<" ";
			pre = trav;
		}
		else
		{
			s.Push(trav);
			trav = trav->rchild;
			while(trav != nullptr)
			{
				s.Push(trav);
				trav = trav->lchild;
			}
		}
	}
}
	template<typename T>
void BinTree<T>::TraverseLevelOrder(BinTreeNode<T> *roo)
{
	Queue<BinTreeNode<T>*> q;
	BinTreeNode<T> *trav;
	if(root == nullptr)
	{
		std::cerr<<"empty tree,can not traverse"<<std::endl;
		throw;
	}
	else
		q.Enqueue(roo);
	while(!q.IsEmpty())
	{
		q.Dequeue(trav);
		std::cout<<trav->data<<" ";
		if(trav->lchild != nullptr)
			q.Enqueue(trav->lchild);
		if(trav->rchild != nullptr)
			q.Enqueue(trav->rchild);
	}
}

template<typename T>
size_t BinTree<T>::Height(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return 0;
	else
	{
		size_t i = Height(roo->lchild);
		size_t j = Height(roo->rchild);
		size_t height = i > j ? i + 1 : j + 1;
		return height;
	}
}

#endif
