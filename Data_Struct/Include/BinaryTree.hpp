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
class Forest;

template<typename T>
BinTreeNode<T>* CreateTreeByInPostOrder(T*,T*,int);

template<typename T>
BinTreeNode<T>* CreateTreeByPreInOrder(T*,T*,int);

template<typename T>
std::set<BinTreeNode<T>*> CreateTreeByInPostOrder_Duplicated(T*,T*,int);

//because of many classes use the BinTreeNode class,there will be a lot of work if the members are private.
template<typename T>
class BinTreeNode
{
	public:
		BinTreeNode():lchild(nullptr),rchild(nullptr){}
		BinTreeNode(T x):data(x),lchild(nullptr),rchild(nullptr){}
		BinTreeNode(BinTreeNode<T> *roo):data(roo->data),lchild(roo->lchild),rchild(roo->rchild){}
		BinTreeNode(BinTreeNode<T> &roo):data(roo.data),lchild(roo.lchild),rchild(roo.rchild){}
		bool isleaf(){if(lchild == nullptr && rchild == nullptr) return true;else return false;}
		BinTreeNode<T>& operator=(const BinTreeNode<T> &p){*this = new BinTreeNode<T>;data = p.data;lchild = p.lchild;rchild = p.rchild;return *this;}
		bool operator > (const BinTreeNode<T> *p){return data > p->data;}
		bool operator==(const BinTreeNode<T> *p){return data == p->data;}
		bool operator==(const BinTreeNode<T> &p){return data == p.data;}
		T data;
		BinTreeNode<T> *lchild;
		BinTreeNode<T> *rchild;
};

template<typename T>
class BinTree
{
	//reconsider the situation:there are some nodes have the same value.
	//In some case,replicated elements can build mutiple binarytree.
	//e.g:inorder:2111211,postorder:2121111,it can be 1( 2 1( 1( 1 2) 1) or 1( 1(2) 1(1(2 1)))
	//remains to solve.
	friend std::set<BinTreeNode<T>*> CreateTreeByInPostOrder_Duplicated<T>(T *ino,T *posto,int n);
	friend BinTreeNode<T>* CreateTreeByPreInOrder<T>(T *preo,T *ino,int n);
	friend BinTreeNode<T>* CreateTreeByInPostOrder<T>(T *ino,T *posto,int n);
	friend class Forest<T>;
	public:
	static T endm;
	BinTree();
	BinTree(T x);
	BinTree(BinTreeNode<T> *roo);
	virtual ~BinTree();
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
	void TraversePreOrder(BinTreeNode<T> *,int );
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
	size_t Depth(BinTreeNode<T> *roo);
	size_t Size();
	void Copy(BinTree<T> &p);
	bool Equal(BinTree<T> &t);
	BinTreeNode<T>* Parent1(BinTreeNode<T> *c,BinTreeNode<T> *p);
	BinTreeNode<T>* Parent2(BinTreeNode<T> *c,BinTreeNode<T> *p);
	size_t Countn0(BinTreeNode<T> *);
	size_t Countn1(BinTreeNode<T> *);
	size_t Countn2(BinTreeNode<T> *);
	void RemoveLeaf(BinTreeNode<T> *&roo);
	void Max(BinTreeNode<T> *&,BinTreeNode<T> *,T &);
	void Reflect(BinTreeNode<T> *&);

	private:
	BinTreeNode<T> *root;
	void destroy(BinTreeNode<T> *ro);
	BinTreeNode<T>* copy(BinTreeNode<T> *orign);
};


template<typename T>
T BinTree<T>::endm;

	template<typename T>
BinTree<T>::BinTree()
{
	root = new BinTreeNode<T>;
}

	template<typename T>
BinTree<T>::BinTree(T x)
{
	root = new BinTreeNode<T>(x);
}

template<typename T>
BinTree<T>::BinTree(BinTreeNode<T> *roo)
{
	root = roo;
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
	destroy(root);
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
			std::cout<<",";
			TraversePreOrder(ro->rchild,ingen);
			std::cout<<" ) ";
			return;
		}

	}
}

template<typename T>
void BinTree<T>::TraversePreOrder(BinTreeNode<T> *ro,int i)
{
	if(ro != nullptr)
	{
		std::cout<<ro->data<<" , "<<i<<std::endl;
		TraversePreOrder(ro->lchild,i + 1);
		TraversePreOrder(ro->rchild,i + 1);
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
	if(roo == nullptr)
	{
		std::cerr<<"empty tree,can not traverse"<<std::endl;
		exit(1);
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

template<typename T>
size_t BinTree<T>::Depth(BinTreeNode<T> *roo)
{
	if(roo != nullptr)
		return 1 + Depth(Parent1(roo,root));
	else
		return 0;
}
template<typename T>
size_t BinTree<T>::Size()
{
	Stack<BinTreeNode<T>*> s;
	size_t Size = 0;
	BinTreeNode<T> *roo = root;
	while(roo != nullptr || !s.IsEmpty())
	{
		if(roo != nullptr)	
		{
			Size++;
			s.Push(roo);
			roo = roo->lchild;
		}
		else
		{
			s.Pop(roo);
			roo = roo->rchild;
		}
	}
	return Size;
}

template<typename T>
bool BinTree<T>::Equal(BinTree<T> &t)
{
	BinTreeNode<T> *rol,*rot;
	Stack<BinTreeNode<T>*> sl;
	Stack<BinTreeNode<T>*> st;
	rol = root;
	rot = t.root;
	while((rol != nullptr && rot != nullptr) || (!sl.IsEmpty() && !st.IsEmpty()))
	{
		if(rol != nullptr && rot != nullptr)
		{
			if(rol != rot)
				return false;
			sl.Push(rol);
			st.Push(rot);
			rol = rol->lchild;
			rot = rot->lchild;
		}
		else
		{
			sl.Pop(rol);
			st.Pop(rot);
			rol = rol->rchild;
			rot = rot->rchild;
		}
	}
	if(Size() == t.Size())
		return true;
	else
		return false;
}

template<typename T>
void BinTree<T>::Copy(BinTree<T> &p)
{
	root = copy(p.root);
}
template<typename T>
BinTreeNode<T>* BinTree<T>::copy(BinTreeNode<T> *origin)
{
	if(origin == nullptr)
		return nullptr;
	BinTreeNode<T> *tmp = new BinTreeNode<T>(origin->data);
	tmp->lchild = copy(origin->lchild);
	tmp->rchild = copy(origin->rchild);
	return tmp;
}

template<typename T>
BinTreeNode<T>* BinTree<T>::Parent1(BinTreeNode<T> *c,BinTreeNode<T> *p)
{
	BinTreeNode<T> *l,*r;
	if(c == root || p == nullptr)
	{
		if(c == root)
			std::cout<<"root don't have a parent"<<std::endl;
		return nullptr;
	}
	if(p->lchild == c || p->rchild == c)
		return p;
	else
	{
		l = Parent1(c,p->lchild);
		r = Parent1(c,p->rchild);
	}
	return l == nullptr ? r : l;
}


template<typename T>
BinTreeNode<T>* BinTree<T>::Parent2(BinTreeNode<T> *c,BinTreeNode<T> *p)
{
	if(c == root)
	{
		std::cout<<"root don't have parent.."<<std::endl;
		return nullptr;
	}
	if(p == nullptr)
		return nullptr;
	if(p->lchild == c || p->rchild == c)
		return p;
	BinTreeNode<T> *q = Parent2(c,p->lchild);
	if(q != nullptr)
		return q;
	else
		return Parent2(c,p->rchild);

}
template<typename T>
size_t BinTree<T>::Countn0(BinTreeNode<T> *trav)
{
	if(trav == nullptr)
		return 0;
	if(trav->isleaf())
		return 1;
	else
		return  Countn0(trav->lchild) + Countn0(trav->rchild);
}
template<typename T>
size_t BinTree<T>::Countn1(BinTreeNode<T> *trav)
{
	if(trav == nullptr)
		return 0;
	if((trav->lchild == nullptr && trav->rchild != nullptr) ||(trav->lchild != nullptr && trav->rchild == nullptr))
	return 1 + Countn1(trav->lchild) + Countn1(trav->rchild);
	else
		return  Countn1(trav->lchild) + Countn1(trav->rchild);
}
template<typename T>
size_t BinTree<T>::Countn2(BinTreeNode<T> *trav)
{
	if(trav == nullptr)
		return 0;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
	return 1 + Countn2(trav->lchild) + Countn2(trav->rchild);
	else
		return  Countn2(trav->lchild) + Countn2(trav->rchild);
}

template<typename T>
void BinTree<T>::RemoveLeaf(BinTreeNode<T> *&roo)
{
	if(roo == nullptr)
		return;
	if(roo->isleaf())
	{
		delete roo;
		roo = nullptr;
	}
	else
	{
		RemoveLeaf(roo->lchild);
		RemoveLeaf(roo->rchild);
	}
}

template<typename T>
void BinTree<T>::Max(BinTreeNode<T> *&M,BinTreeNode<T> *p,T &max)
{
	if(p != nullptr)
	{
		if(p->data > max)
		{
			max = p->data;
			M = p;
		}
		Max(M,p->lchild,max);
		Max(M,p->rchild,max);
	}
}

template<typename T>
void BinTree<T>::Reflect(BinTreeNode<T> *&roo)
{
	if(roo == nullptr)
		return;
	BinTreeNode<T> *tmp;
	tmp = roo->lchild;
	roo->lchild = roo->rchild;
	roo->rchild = tmp;
	Reflect(roo->lchild);
	Reflect(roo->rchild);
}
#endif
