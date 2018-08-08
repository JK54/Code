#ifndef _THREAD_TREE_H
#define _THREAD_TREE_H

#include "sys_comm.h"
#include "BinaryTree.hpp"
#include "Stack.hpp"

template<typename T>
class BinTreeNode;

template <typename T>
class ThreadNode
{
	public:
		T data;
		int ltag,rtag;
		ThreadNode<T> *lchild,*rchild;
		ThreadNode():ltag(0),rtag(0),lchild(nullptr),rchild(nullptr){}
		ThreadNode(T item):data(item),ltag(0),rtag(0),lchild(nullptr),rchild(nullptr){}
		ThreadNode(const BinTreeNode<T> *Bn);
		ThreadNode<T>* operator=(const ThreadNode<T> *p);
};

template<typename T>
class ThreadTree
{
	public:
		ThreadTree():root(new ThreadNode<T>){}
		ThreadTree(T item):root(new ThreadNode<T>(item)){}
		virtual ~ThreadTree();

		ThreadNode<T>* Root();
		virtual void CreateThread(BinTreeNode<T> *ro) = 0;
		virtual	void TraversePreOrder(ThreadNode<T> *roo) = 0;
		virtual	void TraverseInOrder(ThreadNode<T> *roo) = 0;
		virtual	void TraversePostOrder(ThreadNode<T> *current) = 0;
		virtual	ThreadNode<T>* First(ThreadNode<T> *current) = 0;
		virtual	ThreadNode<T>* Last(ThreadNode<T> *current) = 0;
		virtual	ThreadNode<T>* Next(ThreadNode<T> *current) = 0;
		virtual	ThreadNode<T>* Prior(ThreadNode<T> *current) = 0;
		virtual ThreadNode<T> *Parent(ThreadNode<T> *current) = 0;
	protected:
		//data member
		ThreadNode<T> *root;

		void visit(ThreadNode<T> *p);
		//convert BinTreeNode to ThreadNode,ltag and rtag should be assigned by derived threadtree.
		ThreadNode<T>* buildthreadfrombin(ThreadNode<T> *ro,BinTreeNode<T> *roo);
		ThreadNode<T>* parent(ThreadNode<T> *t,ThreadNode<T> *p);

		virtual void createthread(ThreadNode<T> *current,ThreadNode<T> *&pre) = 0;

};

//some feature of prethread:
//1.root is the first node and its lchild is nullptr when lchild is nullptr(convert from BinTreeNode)

template <typename T>
class PreThreadTree:public ThreadTree<T>
{
	public:
		PreThreadTree():ThreadTree<T>(){}
		PreThreadTree(T item):ThreadTree<T>(item){}
		~PreThreadTree() = default;

		virtual	void CreateThread(BinTreeNode<T> *ro) override;
		virtual	void TraversePreOrder(ThreadNode<T> *roo) override;
		virtual	void TraverseInOrder(ThreadNode<T> *roo) override;
		virtual	void TraversePostOrder(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* First(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Last(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Next(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Prior(ThreadNode<T> *current) override;
		virtual ThreadNode<T> *Parent(ThreadNode<T> *current) override;
	protected:
		virtual void createthread(ThreadNode<T> *current,ThreadNode<T> *&pre) override;
};

template <typename T>
class InThreadTree:public ThreadTree<T>
{
	public:
		InThreadTree():ThreadTree<T>(){}
		InThreadTree(T item):ThreadTree<T>(item){}
		~InThreadTree() = default;

		virtual	void CreateThread(BinTreeNode<T> *ro) override;
		virtual	void TraversePreOrder(ThreadNode<T> *roo) override;
		virtual	void TraverseInOrder(ThreadNode<T> *roo) override;
		virtual	void TraversePostOrder(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* First(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Last(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Next(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Prior(ThreadNode<T> *current) override;
		virtual ThreadNode<T> *Parent(ThreadNode<T> *current) override;
		
		ThreadNode<T>* PriorPreOrder(ThreadNode<T> *roo);
		ThreadNode<T>* NextPreOrder(ThreadNode<T> *roo);
		void CompareInsert(ThreadNode<T> *roo,const T &vle);
	protected:
		virtual void createthread(ThreadNode<T> *current,ThreadNode<T> *&pre) override;
};

template <typename T>
class PostThreadTree:public ThreadTree<T>
{
	public:
		PostThreadTree():ThreadTree<T>(){}
		PostThreadTree(T item):ThreadTree<T>(item){}
		~PostThreadTree() = default;

		virtual	void CreateThread(BinTreeNode<T> *ro) override;
		virtual	void TraversePreOrder(ThreadNode<T> *roo) override;
		virtual	void TraverseInOrder(ThreadNode<T> *roo) override;
		virtual	void TraversePostOrder(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* First(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Last(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Next(ThreadNode<T> *current) override;
		virtual	ThreadNode<T>* Prior(ThreadNode<T> *current) override;
		virtual ThreadNode<T> *Parent(ThreadNode<T> *current) override;
	protected:
		virtual void createthread(ThreadNode<T> *current,ThreadNode<T> *&pre) override;
};
//-------------ThreadNode begin--------------------
//for buildthreadfrombin(),initialize the tag.make the createthread concise.
	template<typename T>
ThreadNode<T>::ThreadNode(const BinTreeNode<T> *Bn)
{
	data = Bn->data;
	if(Bn->lchild == nullptr)
		ltag = 1;
	else
		ltag = 0;
	if(Bn->rchild == nullptr)
		rtag = 1;
	else
		rtag = 0;
}

template<typename T>
ThreadNode<T>* ThreadNode<T>::operator=(const ThreadNode<T> *p)
{
	data = p->data;
	ltag = p->ltag;
	rtag = p->rtag;
	lchild = p->lchild;
	rchild = p->rchild;
	return this;
}
//--------------------ThreadNode end-------------------

//----------------ThreadTree begin----------------
template<typename T>
ThreadNode<T>* ThreadTree<T>::Root()
{
	return root;
}
template<typename T>
void ThreadTree<T>::visit(ThreadNode<T> *p)
{
	std::cout<<p->data<<" ";
}
template<typename T>
ThreadTree<T>::~ThreadTree()
{
	Stack<ThreadNode<T>*> s;
	ThreadNode<T>* tmp = root;
	s.Push(root);
	//preorder traverse is the best way to build destruct,because it only visit node for one time,while postorder will visit every root node twice(the pre pointer assigned the delete root pointer).inorder also works well.choose one from inorder, preorder and levelorder is ok.
	while(!s.IsEmpty())
	{
		s.Pop(tmp);
		if(tmp->rtag == 0)
			s.Push(tmp->rchild);
		if(tmp->ltag == 0)
			s.Push(tmp->lchild);
		delete tmp;
		tmp = nullptr;
	}
}	

//init the base thread tree,without thread pointer filled.
template<typename T>
ThreadNode<T>* ThreadTree<T>::buildthreadfrombin(ThreadNode<T> *ro,BinTreeNode<T> *roo)
{
	if(roo == nullptr)
		return nullptr;
	else
	{
		ro = new ThreadNode<T>(roo);
		ro->lchild = buildthreadfrombin(ro->lchild,roo->lchild);
		ro->rchild = buildthreadfrombin(ro->rchild,roo->rchild);
		return ro;
	}
}

//because the preoder and postorder thread break off in full scale node(ltag and rtag are 0),and we can not find more thread from the visited nodes,searching from root(other node higher than current works,too) is the only feasible way.
template<typename T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T> *t,ThreadNode<T> *p)
{
	if(t == nullptr)
		return nullptr;
	if((p->lchild == t &&p->ltag == 0) || (p->rchild == t && p->rtag == 0))
		return p;
	if(ThreadNode<T> *q = parent(t,p->lchild))
		return q;
	else
		return parent(t,p->rchild);
}

//----------------ThreadTree end------------------
//-------------------PreThreadTree begin----------------
template<typename T>
ThreadNode<T>* PreThreadTree<T>::First(ThreadNode<T> *current)
{
	//current node is the first node for prethread tree.
	return current;
}
template<typename T>
ThreadNode<T>* PreThreadTree<T>::Last(ThreadNode<T> *current)
{
	if(current != nullptr && current->rtag == 0)
		return Last(current->rchild);
	else if((current != nullptr && current->ltag == 0))
		return Last(current->lchild);
	else
		return current;
}
template<typename T>
ThreadNode<T>* PreThreadTree<T>::Next(ThreadNode<T> *current)
{
	if(current->ltag == 0)
		return current->lchild;
	else
		return current->rchild;
}
template<typename T>
ThreadNode<T>* PreThreadTree<T>::Prior(ThreadNode<T> *current)
{
	if(current != nullptr)
	{
		if(current->ltag == 1)
			return current->lchild;
		else
		{
			ThreadNode<T> *q = Parent(current);
			if(q->lchild == current)
				return q;
			else
				return Last(q->lchild);
		}
	}
	else
	{
		std::cout<<"nullptr don't have a prior node.."<<std::endl;
		return nullptr;
	}
}

template<typename T>
ThreadNode<T>* PreThreadTree<T>::Parent(ThreadNode<T> *current)
{
	if(current == this->root)
	{
		std::cout<<"root node don't have a parent"<<std::endl;
		return nullptr;
	}
	ThreadNode<T> *p = current;
	while(!((p->lchild == current && p->ltag == 0) || (p->rchild == current && p->rtag == 0)))
	{
		if(p->ltag == 1)
			p = p->lchild;
		else
			p = this->parent(p,this->root);
	}
	return p;
}

template<typename T>
void PreThreadTree<T>::CreateThread(BinTreeNode<T> *p)
{
	this->root = this->buildthreadfrombin(this->root,p);
	ThreadNode<T> *pre = nullptr;
	ThreadNode<T> *trav = this->root;
	/* //using preorder traverse to build thread,it works,and the overload recursive method exist a fatal problem:when it come the First node of subtree,in this moment,current->lchild = pre,it will goes on an infinite loop:pre = current,CreateThread(pre,current)->CreteThread(current,pre).it need to be debugged. */
	//the overload recursive solved,the key problem is that if the lchild and rchild is nullptr,we should not recurse it.And I thought the traverse is also helpful to understand the thread,keep it here.
   /*  Stack<ThreadNode<T>*> s; */
	// if(trav->rchild != nullptr)
		// s.Push(trav->rchild);
	// if(trav->lchild != nullptr)
		// s.Push(trav->lchild);
	// while(!s.IsEmpty())
	// {
		// pre = trav;
		// s.Pop(trav);
		// if(trav->rchild != nullptr)
			// s.Push(trav->rchild);
		// if(trav->lchild != nullptr)
			// s.Push(trav->lchild);
		// if(pre->rchild == nullptr)
			// pre->rchild = trav;
		// if(trav->lchild == nullptr)
			// trav->lchild = pre;
	/* } */
	createthread(trav,pre);
}

template<typename T>
void PreThreadTree<T>::createthread(ThreadNode<T> *current,ThreadNode<T> *&pre)
{
	//ltag and rtag are dealed with buildthreadfrombin,so do not need to handle them
	if(current == nullptr)
		return;
	if(current->lchild == nullptr)
		current->lchild = pre;
	if(pre != nullptr && pre->rchild == nullptr)
		pre->rchild = current;
	pre = current;
	//need to prevent the direction turn to previous
	if(current->ltag == 0)
		createthread(current->lchild,pre);
	if(current->rtag == 0)
		createthread(current->rchild,pre);
}

template<typename T>
void PreThreadTree<T>::TraversePreOrder(ThreadNode<T> *roo)
{
	if(roo == nullptr)
	{
		std::cout<<"traverse begin at nullptr"<<std::endl;
		exit(1);
	}
	ThreadNode<T> *p = First(roo);
	while(p != nullptr)
	{
		std::cout<<p->data<<" ";
		p = Next(p);
	}
}

template<typename T>
void PreThreadTree<T>::TraverseInOrder(ThreadNode<T> *roo)
{
   /*  ThreadNode<T> *trav = roo; */
	// ThreadNode<T> *pre = nullptr;
	// ThreadNode<T> *last = roo;
	// //search for first node inorder
	// while(trav->ltag == 0)
		// trav = trav->lchild;
	// while(last->rtag == 0)
		// last = last->rchild;
	// while(trav != last)
	// {
		// this->visit(trav);
		// if(trav->rtag == 1)
			// trav = Parent(trav);
		// else if(trav->rtag == 0 && trav != pre)
		// {
			// pre = trav;
			// trav = trav->rchild;
			// while(trav->ltag == 0)
				// trav = trav->lchild;
		// }
	/* } */
}
template<typename T>
void PreThreadTree<T>::TraversePostOrder(ThreadNode<T> *roo)
{}
//------------------PreThreadTree end-------------------
//-----------------InThreadTree begin-----------------
	template<typename T>
ThreadNode<T>* InThreadTree<T>::First(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current;
	while(p->ltag == 0)
		p = p->lchild;
	return p;
}

	template<typename T>
ThreadNode<T>* InThreadTree<T>::Last(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current;
	while(p->rtag == 0)
		p = p->rchild;
	return p;
}
	template<typename T>
ThreadNode<T>* InThreadTree<T>::Next(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current->rchild;
	if(current->rtag == 0)
		return First(p);
	else
		return p;
}
	template<typename T>
ThreadNode<T>* InThreadTree<T>::Prior(ThreadNode<T> *current)
{
	ThreadNode<T> *p = current->lchild;
	if(current->ltag == 0)
		return Last(p);
	else
		return p;
}

	template<typename T>
ThreadNode<T>* InThreadTree<T>::Parent(ThreadNode<T> *current)
{
	if(current == ThreadTree<T>::root)
		return nullptr;
	ThreadNode<T> *p = current;
	while(p->ltag == 0)
		p= p->lchild;
	//there are 2 situation:
	//1.leap to the most left child,and jump to right.It does not be always successful when the most left treenode of current node is the first node of the threadtree.
	//2.leap to the most right child,jump tp left.as above,the most right might be last node
	//so we need two way to find the Parent.
	//In a nutshell,considering the in order sequence:LNR,the node may be L or R,so we need two directions.
	if(p->lchild != nullptr)
	{
		p = p->lchild;
		while(p != nullptr && p->lchild != current && p->rchild != current)
			p = p->rchild;
	}
	if(p == nullptr || p->lchild == nullptr)
	{
		p = current;
		while(p->rtag == 0)
			p = p->rchild;
		p = p->rchild;
		while(p != nullptr && p->lchild != current && p->rchild != current)
			p = p->lchild;
	}
	return p;

}
//why preorder need to if statement ,but inoder don't need it?
//the sequence cause the different.it will blocked by the first judgement.
template<typename T>
void InThreadTree<T>::createthread(ThreadNode<T> *current,ThreadNode<T> *&pre)
{
	if(current == nullptr)
		return;
	createthread(current->lchild,pre);
	//ltag and rtag was handled by the buildthreadfrombin
	if(current->lchild == nullptr)
		current->lchild = pre;
	if(pre != nullptr && pre->rchild == nullptr)
		pre->rchild = current;
	pre = current;
	createthread(current->rchild,pre);
}

	template<typename T>
void InThreadTree<T>::CreateThread(BinTreeNode<T> *ro)
{
	ThreadNode<T> *pre = nullptr;
	ThreadTree<T>::root = ThreadTree<T>::buildthreadfrombin(ThreadTree<T>::root,ro);
	if(ThreadTree<T>::root != nullptr)
		createthread(ThreadTree<T>::root,pre);
}

	template<typename T>
void InThreadTree<T>::TraversePreOrder(ThreadNode<T> *current)
{
	if(current == nullptr)
		return;
	else
	{
		ThreadNode<T> *p = current;
		while(p != nullptr)
		{
			this->visit(p);
			if( p->ltag == 0)
				p = p->lchild;
			else if(p->rtag == 0)
				p = p->rchild;
			else
			{
				//when the leaf node comes to its ancestor which own lchild,change to the lchild.
				while(p != nullptr && p->rtag == 1)
					p = p->rchild;
				if( p != nullptr)
					p = p->rchild;
			}
		}
	}
}

	template<typename T>
void InThreadTree<T>::TraverseInOrder(ThreadNode<T> *roo)
{
	if(roo == nullptr)
		return;
	else
	{
		for(ThreadNode<T> *tmp = First(roo);tmp != nullptr;tmp =Next(tmp))
			std::cout<<tmp->data<<" ";
	}
}



	template<typename T>
void InThreadTree<T>::TraversePostOrder(ThreadNode<T> *current)
{
	if(current == nullptr)
		return;
	else
	{
		ThreadNode<T> *p = current;
		ThreadNode<T> *q;
		while(p->ltag == 0 || p->rtag == 0)
			if(p->ltag == 0)
				p = p->lchild;
			else if( p->rtag == 0)
				p = p->rchild;
		this->visit(p);
		while((q = Parent(p)) != nullptr)
		{
			//if p is rchild of q,then it's time to visit "ThreadTree<T>::root"(q);Or the Parent don't have a rchild,it also need to visit q.
			if (q->rchild == p || q->rtag == 1)
				p = q;
			// p is not the rchild of q
			else
			{
				p = q->rchild;
				while(p->ltag == 0 || p->rtag == 0)
					if(p->ltag == 0)
						p = p->lchild;
					else if( p->rtag == 0)
						p = p->rchild;
			}
			this->visit(p);
		}
	}
}
template<typename T>
ThreadNode<T>* InThreadTree<T>::PriorPreOrder(ThreadNode<T> *roo)
{
	if(roo == ThreadTree<T>::root)
	{
		std::cout<<"root is the first node preoder"<<std::endl;
		return nullptr;
	}
	ThreadNode<T> *tmp = roo;
	ThreadNode<T> *p = Parent(roo);
	if(p->lchild == roo)
		tmp = p;
	else
	{
		tmp = p->lchild;
		while(tmp->ltag == 0 || tmp->rtag == 0)
		{
			while(tmp->rtag == 0)
				tmp = tmp->rchild;
			while(tmp->ltag == 0)
				tmp = tmp->lchild;
		}
	}
	return tmp;
}
template<typename T>
ThreadNode<T>* InThreadTree<T>::NextPreOrder(ThreadNode<T> *roo)
{
	ThreadNode<T> *tmp;
	if(roo->ltag == 0)
		tmp = roo->lchild;
	else if(roo->rtag == 0)
		tmp = roo->rchild;
	else
	{
		tmp = roo;
		while(tmp != nullptr && tmp->rtag == 1)
			tmp = tmp->rchild;
		if(tmp != nullptr)
			tmp = tmp->rchild;
	}
	return tmp;
}

template<typename T>
void InThreadTree<T>::CompareInsert(ThreadNode<T> *roo,const T &vle)
{
	ThreadNode<T> *tmp = new ThreadNode<T>(vle);
	ThreadNode<T> *lc = roo->lchild;
	if(roo->ltag == 1)
	{
		tmp->rchild = roo;
		tmp->rchild = roo->lchild;
	}
	else
	{
		if(tmp->data < lc->data)
		{
			tmp->rchild = lc;
			tmp->rtag = 0;
			tmp->ltag = lc->ltag;
			tmp->lchild = lc->lchild;
			while(lc->ltag == 0)
				lc = lc->lchild;
			lc->lchild = tmp;
		}
		else
		{
			tmp->lchild = lc;
			tmp->ltag = 0;
			tmp->rchild = roo;
			tmp->rtag = 1;
			while(lc->rtag == 0)
				lc = lc->rchild;
			lc->rchild = tmp;
		}
	}
	roo->lchild = tmp;
	roo->ltag = 0;
}
//-----------------------InThreadTree end-------------------------------

//-------------PostThreadTree begin---------------
template<typename T>
ThreadNode<T>* PostThreadTree<T>::First(ThreadNode<T> *roo)
{
	if(roo == nullptr)
		return nullptr;
   if(roo->ltag == 0)
  	 	return First(roo->lchild);
   else if(roo->rtag == 0)
   		return First(roo->rchild);
   else
   		return roo;
}

template<typename T>
ThreadNode<T>* PostThreadTree<T>::Last(ThreadNode<T> *roo)
{
	return roo;
}

template<typename T>
ThreadNode<T>* PostThreadTree<T>::Next(ThreadNode<T> *roo)
{
	//root don't have a next node.
	if(roo == this->root)
		return nullptr;
	ThreadNode<T> *tmp = roo->rchild;
	if(roo->rtag == 0)
	{
		tmp = Parent(roo);
		if(tmp->lchild == roo && tmp->rtag == 0)
			tmp = First(tmp->rchild);
	}
	return tmp;
}

template<typename T>
ThreadNode<T>* PostThreadTree<T>::Prior(ThreadNode<T> *roo)
{
	if(roo == nullptr)
		exit(1);
	//if roo is the first node,it return nullptr naturally,extra judge is unncessary.
	ThreadNode<T> *tmp = roo->lchild;
	if(roo->ltag == 0 && roo->rtag == 0)
			tmp = roo->rchild;
	return tmp;
}

template<typename T>
ThreadNode<T>* PostThreadTree<T>::Parent(ThreadNode<T> *roo)
{
	if(roo == this->root)
	{
		std::cout<<"root don't have a parent"<<std::endl;
		return nullptr;
	}
	ThreadNode<T> *tmp = roo;
	while(!((tmp->lchild == roo && tmp->ltag == 0) || (tmp->rchild == roo && tmp->ltag == 0)))
	{
		if(tmp->rtag == 1)
			tmp = tmp->rchild;
		else
			tmp = this->parent(tmp,this->root);
	}
	return tmp;
}

template<typename T>
void PostThreadTree<T>::CreateThread(BinTreeNode<T> *ro)
{
	ThreadTree<T>::root = this->buildthreadfrombin(this->root,ro);
	ThreadNode<T> *trav = ThreadTree<T>::root;
	ThreadNode<T> *pre = nullptr;
	createthread(trav,pre);
}

template<typename T>
void PostThreadTree<T>::createthread(ThreadNode<T> *trav,ThreadNode<T> *&pre)
{
	if(trav == nullptr)
		return;
	createthread(trav->lchild,pre);
	createthread(trav->rchild,pre);
	if(trav->lchild == nullptr)
		trav->lchild = pre;
	if(pre != nullptr && pre->rchild == nullptr)
		pre->rchild = trav;
	pre = trav;
}

template<typename T>
void PostThreadTree<T>::TraversePostOrder(ThreadNode<T> *current)
{
	for(ThreadNode<T> * tmp = First(current);tmp != nullptr;tmp = Next(tmp))
		std::cout<<tmp->data<<" ";
	std::cout<<std::endl;
}
template<typename T>
void PostThreadTree<T>::TraverseInOrder(ThreadNode<T> *current){}
template<typename T>
void PostThreadTree<T>::TraversePreOrder(ThreadNode<T> *current){}
//-----------PostThreadTree end-------------------	
#endif
