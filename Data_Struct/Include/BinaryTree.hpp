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
		BinTreeNode<T>* operator=(const BinTreeNode<T> *p){*this = new BinTreeNode<T>;data = p->data;lchild = p->lchild;rchild = p->rchild;return this;}
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
	~BinTree();
	// BinTree(const BinTree<T> &s);

	bool operator==(const BinTree<T> &s);
	bool operator!=(const BinTree<T> &s);//in fact,the opposite value of "==".
	// BinTree<T>& operator=(const BinTree<T> &s);

	//get root node and modify endmark
	BinTreeNode<T>*& Root(){return root;}
	BinTreeNode<T>* uRoot(){return root;}
	void SetMark(T x){endm = x;}
	void CreateTreePreOrder(BinTreeNode<T> *&ro,std::istream &is);
	//recursive traverse
	//bool type variable "ingen" control the output in genlist format(1) or not(0)
	void TraversePreOrder(BinTreeNode<T> *);
	void TraversePreOrder(BinTreeNode<T> *ro,bool ingen);
	void TraversePreOrder2(BinTreeNode<T> *,int );
	void TraverseInOrder(BinTreeNode<T> *ro);
	void TraversePostOrder(BinTreeNode<T> *ro);
	void TraverseDoubleOrder(BinTreeNode<T> *ro);
	//no-recursive traverse
	void TraversePreOrder_NR1(BinTreeNode<T> *roo);
	void TraversePreOrder_NR2(BinTreeNode<T> *roo);
	void TraversePreOrder_NR3(BinTreeNode<T> *roo);
	void TraverseInOrder_NR(BinTreeNode<T> *roo);
	void TraversePostOrder_NR(BinTreeNode<T> *roo);
	void TraverseLevelOrder(BinTreeNode<T> *roo);

	//use traverse to complete
	size_t Height(BinTreeNode<T> *roo);
	size_t Height();
	size_t Depth(BinTreeNode<T> *roo);
	size_t Size();
	void Copy(BinTree<T> &p);
	void Copy(BinTreeNode<T> *p);
	bool Equal(BinTree<T> &t);
	BinTreeNode<T>* Parent1(BinTreeNode<T> *c,BinTreeNode<T> *p);
	BinTreeNode<T>* Parent2(BinTreeNode<T> *c,BinTreeNode<T> *p);
	size_t Countn0(BinTreeNode<T> *);
	size_t Countn1(BinTreeNode<T> *);
	size_t Countn2(BinTreeNode<T> *);
	void Countn2(BinTreeNode<T> *,int &n);
	void RemoveLeaf(BinTreeNode<T> *&roo);
	void Max(BinTreeNode<T> *&,BinTreeNode<T> *,T &);
	void Reflect(BinTreeNode<T> *&);
	int PrintAncient(BinTreeNode<T> *p,T x,T path[],int level,int &count);
	int PrintAncient(BinTreeNode<T> *p,BinTreeNode<T> *q,BinTreeNode<T> *path[],int level,int &count);
	BinTreeNode<T>* FindPosPreOrder(BinTreeNode<T> *,int &);
	void FindPath(BinTreeNode<T> *I,BinTreeNode<T> *J,T *path,size_t &len);
	void LeafCount(BinTreeNode<T> *);
	void LeafCount(BinTreeNode<T> *,BinTreeNode<T> *leaf[],int lev[],int level,int &num);
	void Width(BinTreeNode<T> *,int width[],int &max);
	bool IsCBT();
	bool IsCBT(BinTreeNode<T> *roo);
	void TransPre2Post(T pre[],T post[],int s1,int t1,int s2,int t2);

	protected:
	BinTreeNode<T> *root;
	void destroy(BinTreeNode<T> *ro);
	BinTreeNode<T>* copy(BinTreeNode<T> *origin);
};

//declare static parameter.
template<typename T>
T BinTree<T>::endm;
//constructor and destructor
template<typename T>
BinTree<T>::BinTree()
{
	root =  nullptr;
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
void BinTree<T>::destroy(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return;
	else
	{
		destroy(roo->lchild);
		destroy(roo->rchild);
		delete roo;
		roo = nullptr;
	}
}

template<typename T>
BinTree<T>::~BinTree()
{
	destroy(root);
	root = nullptr;
}

//create tree
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

//traverse
template<typename T>
void BinTree<T>::TraversePreOrder(BinTreeNode<T> *roo)
{
	while(roo != nullptr)
	{
		std::cout<<roo->data<<" ";
		TraversePreOrder(roo->lchild);
		roo = roo->rchild;
	}
}
	
template<typename T>
void BinTree<T>::TraversePreOrder(BinTreeNode<T> *ro,bool ingen)
{
	if(ro == nullptr)
		return;
	std::cout<<ro->data<<" ";
	if(ingen == true)
		std::cout<<"( ";
	TraversePreOrder(ro->lchild,ingen);
	if(ingen == true)
		std::cout<<",";
	TraversePreOrder(ro->rchild,ingen);
	if(ingen == true)
		std::cout<<" ) ";
}

template<typename T>
void BinTree<T>::TraversePreOrder2(BinTreeNode<T> *ro,int i)
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
	if(ro != nullptr)
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
		return;
	else
	{
		TraversePostOrder(ro->lchild);
		TraversePostOrder(ro->rchild);
		std::cout<<ro->data<<" ";
		return;
	}
}

template<typename T>
void BinTree<T>::TraverseDoubleOrder(BinTreeNode<T> *ro)
{
	if(ro != nullptr)
	{
		std::cout<<ro->data<<" ";
		TraverseDoubleOrder(ro->lchild);
		std::cout<<ro->data<<" ";
		TraverseDoubleOrder(ro->rchild);
	}
}
template<typename T>
void BinTree<T>::TraversePreOrder_NR1(BinTreeNode<T> *roo)
{
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *trav = roo;
	s.Push(trav);
	while(s.Pop(trav))
	{
		std::cout<<trav->data<<" ";
		if(trav->rchild != nullptr)
			s.Push(trav->rchild);
		if(trav->lchild != nullptr)
			s.Push(trav->lchild);
	}
}

template<typename T>
void BinTree<T>::TraversePreOrder_NR2(BinTreeNode<T> *roo)
{
	Stack<BinTreeNode<T>*> s;
	BinTreeNode<T> *trav = roo;
	s.Push(trav);
	while(!s.IsEmpty())
	{
		s.Pop(trav);
		std::cout<<trav->data<<" ";
		if(trav->rchild != nullptr)
			s.Push(trav->rchild);
		if(trav->lchild != nullptr)
			s.Push(trav->lchild);
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
size_t BinTree<T>::Height()
{
	if(root == nullptr)
		return 0;
	size_t h = 0,tmp = 1;
	Stack<BinTreeNode<T>*> S;
	Stack<size_t> H,TMP;
	BinTreeNode<T> *p = root;
	S.Push(p);
	H.Push(tmp);
	while(!S.IsEmpty())
	{
		S.Pop(p);
		TMP.Pop(tmp);
		if(p->lchild != nullptr || p->rchild != nullptr)
		{
			tmp++;
			if(p->rchild != nullptr)
			{
				S.Push(p->rchild);
				TMP.Push(tmp);
			}
			if(p->lchild != nullptr)
			{
				S.Push(p->lchild);
				TMP.Push(tmp);
			}
		}
		else	
			H.Push(tmp);
	}
	while(!H.IsEmpty())
	{
		H.Pop(tmp);
		if(h < tmp)
			h = tmp;
	}
	return h;
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
	sl.Push(rol);
	st.Push(rot);
	while(!sl.IsEmpty() && !st.IsEmpty())
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
void BinTree<T>::Copy(BinTreeNode<T> *p)
{
	root = copy(p);
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
		return nullptr;
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
		return nullptr;
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
void BinTree<T>::Countn2(BinTreeNode<T> *trav,int &n)
{
	if(trav == nullptr)
		return;
	if(trav->lchild != nullptr && trav->rchild != nullptr)
		n++;
	Countn2(trav->lchild,n);
	Countn2(trav->rchild,n);
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

//level init as 1 when called.
template<typename T>
int BinTree<T>::PrintAncient(BinTreeNode<T> *p,T x,T *path,int level,int &count)
{
	if(p != nullptr)
	{
		path[level - 1] = p->data;
		if(p->data == x)
		{
			count = level;
			return 1;
		}
		if(PrintAncient(p->lchild,x,path,level + 1,count))
			return 1;
		return	PrintAncient(p->rchild,x,path,level+ 1,count);
	}
	return 0;
}

//usable for repeating elements.
template<typename T>
int BinTree<T>::PrintAncient(BinTreeNode<T> *p,BinTreeNode<T> *q,BinTreeNode<T> *path[],int level,int &count)
{
	if(p != nullptr)
	{
		path[level - 1] = p;
		//here the refined operator won't be called,it must be used as the form:p->operator=(),because p is pointer.
		if(p == q)
		{
			count = level;
			for(int i = 0 ;i<count;++i)
				std::cout<<path[i]->data<<" ";
			std::cout<<std::endl;
			return 1;
		}
		if(PrintAncient(p->lchild,q,path,level + 1,count))
			return 1;
		return PrintAncient(p->rchild,q,path,level+ 1,count);
	}
	return 0;
}

template<typename T>
BinTreeNode<T>* BinTree<T>::FindPosPreOrder(BinTreeNode<T> *roo,int &k)
{
	if(roo == nullptr)
		return nullptr;
	//define the sequence num of root is 1
	if(--k == 0)
	{
		std::cout<<"the value of position k preorder is "<<roo->data<<std::endl;
		return roo;
	}
	BinTreeNode<T> *tmp1,*tmp2;
	tmp1 = FindPosPreOrder(roo->lchild,k);
	tmp2 = FindPosPreOrder(roo->rchild,k);
	return tmp1 == nullptr? tmp2:tmp1;
}

template<typename T>
void BinTree<T>::FindPath(BinTreeNode<T> *I,BinTreeNode<T>* J,T path[],size_t &len)
{

	BinTreeNode<T> **pathI = new BinTreeNode<T>* [Size()];
	BinTreeNode<T> **pathJ = new BinTreeNode<T>* [Size()];
	int i,j,k = 0;
	int countI = 0,countJ = 0;
	PrintAncient(root,I,pathI,1,countI);
	PrintAncient(root,J,pathJ,1,countJ);
	if(!countI || !countJ)
	{
		std::cout<<"invalid node"<<std::endl;
		exit(1);
	}
	//skip common ancestor and link
	for(i = 0;i < countI && i <countJ;++i)
		if(pathI[i] != pathJ[i])
			break;
	i--;
	for(j = countI - 1; j > i;j--,k++)
			path[k] = pathI[j]->data;
	for(j = i;j < countJ;j++,k++)
			path[k] = pathJ[j]->data;
	//len is the path of nodes,the len of path between 2 node is 1 unit.
	len = k - 1;
	//print path and len
	std::cout<<"len of path is "<<len<<std::endl;
	for(k = 0;k <= len;k++)
		std::cout<<path[k]<<" ";
	std::cout<<std::endl;
	delete [] pathI;
	delete [] pathJ;
}

template<typename T>
void BinTree<T>::LeafCount(BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		exit(1);
	Queue<BinTreeNode<T>*> q;
	Queue<BinTreeNode<T>*> leaf;
	Queue<size_t> depth;
	size_t tmp;
	BinTreeNode<T> *p;
	q.Enqueue(roo);
	while(!q.IsEmpty())
	{
		q.Dequeue(p);
		//I can not think out a method to count the level with linkedlist queue.so here call Depth() to count the level.the second recursion function is easier to write.
		if(p->isleaf())
		{
			leaf.Enqueue(p);
			tmp = Depth(p);
			depth.Enqueue(tmp);
		}
		if(p->lchild != nullptr)
			q.Enqueue(p->lchild);
		if(p->rchild != nullptr)
			q.Enqueue(p->rchild);
	}
	while(leaf.Dequeue(p))
		std::cout<<p->data<<" ";
	std::cout<<std::endl;
	while(depth.Dequeue(tmp))
		std::cout<<tmp<<" ";
	std::cout<<std::endl;
}

//init value of level is 1,num is 0
template<typename T>
void BinTree<T>::LeafCount(BinTreeNode<T> *roo,BinTreeNode<T> **leaf,int *lev,int level,int &num)
{
	if(roo == nullptr)
		return;
	if(roo->isleaf())
	{
		leaf[num] = roo;
		lev[num] = level;
		num++;
	}
	LeafCount(roo->lchild,leaf,lev,level + 1,num);
	LeafCount(roo->rchild,leaf,lev,level + 1,num);
}

template<typename T>
void BinTree<T>::Width(BinTreeNode<T> *roo,int width[],int &max)
{
	if(roo == nullptr)
	{
		std::cout<<"null.."<<std::endl;
		exit(1);
	}
	BinTreeNode<T> *trav = roo;
	int size = Size();
	BinTreeNode<T> **queue = new BinTreeNode<T>*[size];
	int front = 0,last = 1,rear = 0;
	int num = 0,level = 1;
	rear = (rear + 1)%size;
	queue[rear] = trav;   
	while(front != rear)
	{
		front = (front + 1) % size;
		trav = queue[front];
		num++;
		if(trav->lchild != nullptr)
		{
			rear = (rear + 1) % size;
			queue[rear] = trav->lchild;
		}
		if(trav->rchild != nullptr)
		{
			rear = (rear + 1) % size;
			queue[rear] = trav->rchild;
		}
		if(front == last)
		{
			last = rear;
			width[level] = num;
			num = 0;
			level++;
		}
	}
	max = width[1];
	for(int i = 1;i < level;i++)
		max = max > width[i]? max : width[i];
	delete [] queue;
}

template<typename T>
bool BinTree<T>::IsCBT()
{
	int height = Height(root);
	int size = Size();
	if(height == static_cast<int>(log10(size)/log10(2)) + 1)
		return true;
	else
		return false;
}

template<typename T>
bool BinTree<T>::IsCBT(BinTreeNode<T> *roo)
{
	int size = 2 * Size();
	int front = 0,rear = 0;
	BinTreeNode<T> *trav;
	BinTreeNode<T> **queue = new BinTreeNode<T>*[size];
	for(int i = 0;i < size;i++)
		queue[i] = nullptr;
	queue[rear++] = roo;
	while(front != rear)
	{
		trav = queue[front];
		queue[front] = nullptr;
		front = (front + 1) % size;
		if(trav == nullptr)
		{
			while(front != rear)
			{
				trav = queue[front];
				queue[front] = nullptr;
				front = (front + 1) % size;
				if(trav != nullptr)
					return false;
			}
		}
		else
		{
			queue[rear]= trav->lchild;
			rear = (rear + 1) %size;
			queue[rear] = trav->rchild;
			rear = (rear + 1) %size;
		}
	}
	delete [] queue;
	return true;
}

template<typename T>
void BinTree<T>::TransPre2Post(T *pre,T *post,int s1,int t1,int s2,int t2)
{
	int n = t1 - s1 + 1;
	int m = (n - 1)/2;
	if(n)
	{
		post[t2] = pre[s1];
		TransPre2Post(pre,post,s1 + 1,s1 + m,s2,s2 + m - 1);
		TransPre2Post(pre,post,t1 - m + 1,t1,t2 - m,t2-1);
	}
}
#endif
