#ifndef _BST_H
#define _BST_H

#include "BinaryTree.hpp"

template<typename T>
class AVLTree;

template<typename T>
class BSTree:public BinTree<T>
{
	public:
		BSTree():BinTree<T>(){}
		BSTree(T x):BinTree<T>(x){}
		virtual ~BSTree() = default;

		void CreateBST(std::istream &is);

		bool Insert(const T &vle);
		bool Search(const T &vle);
		bool Remove_NR(const T &vle);
		bool Remove(const T &vle,BinTreeNode<T> *&roo);
};

template<typename T>
class AVLTreeNode : public BinTreeNode<T>
{
	friend class AVLTree<T>;
	public:
	/* AVLTreeNode():lchild(nullptr),rchild(nullptr),bf(0){} */
	/* AVLTreeNode(T x):data(x),lchild(nullptr),rchild(nullptr),bf(0){} */
	AVLTreeNode():BinTreeNode<T>(),bf(0){}
	AVLTreeNode(T x):BinTreeNode<T>(x),bf(0){}

	private:
	/* T data; */
	// AVLTreeNode<T> *lchild;
	/* AVLTreeNode<T> *rchild; */
	int bf;//balance factor,bf = Height(rchild) - Height(lchild).it only has values of -1,0,1
};

template<typename T>
class AVLTree:public BSTree<T>//almost useless heritage.
{
	public:
		AVLTree():root(new AVLTreeNode<T>()){}
		AVLTree(T x):root(new AVLTreeNode<T>(x)){}
		~AVLTree() = default;

		AVLTreeNode<T>* Root(){return root;}
		
		//the following member functions are copies of binarytree or binarysearchtree(only differ in parameter type).Although AVLTree is the son of BST,but they operate in different node type,BinTreeNode and AVLTreeNode,I have thought of making AVLTreeNode the son of BinTreeNode,but it causes an unexpected problem:u can not point to base class with derived class type pointer.ps:the base class have pointer point to the same class of itself,when derived class 
		// bool Remove(const T &vle,AVLTreeNode<T> *&roo);
		// virtual bool Insert(const T &vle) override;
		// virtual bool Search(const T &vle) override;
		// void TraversePreOrder(AVLTreeNode<T> *ro,bool ingen);
		// void TraverseLevelOrder(AVLTreeNode<T> *roo);
		//-----------------------------------------------------------------------
		
		
		
	private:
		AVLTreeNode<T> *root;

		void balance();
		void rotatel(AVLTreeNode<T> *roo);
		void rotater(AVLTreeNode<T> *roo);
		void rotatelr(AVLTreeNode<T> *roo);
		void rotaterl(AVLTreeNode<T> *roo);
		// size_t height(AVLTreeNode<T> *roo);
};

//--------------------------------------BSTree------------------------------------------

	template<typename T>
void BSTree<T>::CreateBST(std::istream &is)
{
	T data;
	while(is>>data)
		Insert(data);
}

	template<typename T>
bool BSTree<T>::Insert(const T &vle)
{
	BinTreeNode<T> *tmp = new BinTreeNode<T>(vle);
	BinTreeNode<T> *roo = BinTree<T>::root;
	while(roo != nullptr)
	{
		if(roo->data > vle)
		{
			if(roo->lchild != nullptr)
				roo = roo->lchild;
			else
				break;
		}
		else if(roo->data < vle)
		{
			if(roo->rchild != nullptr)
				roo = roo->rchild;
			else
				break;
		}
		else
		{
			std::cerr<<"repeating element.."<<std::endl;
			return false;
		}
	}
	if(vle > roo->data)
		roo->rchild = tmp;
	else
		roo->lchild = tmp;
	return true;
}

	template<typename T>
bool BSTree<T>::Search(const T &vle)
{
	if(BinTree<T>::root == nullptr)
	{
		std::cout<<"empty tree..."<<std::endl;
		return false;
	}
	BinTreeNode<T> *tmp = BinTree<T>::root;
	while(tmp->data != vle)
	{
		if(tmp->data > vle && tmp->lchild != nullptr)
			tmp = tmp->lchild;
		else if(tmp->data < vle && tmp->rchild != nullptr)
			tmp = tmp->rchild;
		else
			return false;
	}
	return true;
}

	template<typename T>
bool BSTree<T>::Remove_NR(const T &vle)
{
	if(Search(vle) == false)
		return false;
	else
	{
		BinTreeNode<T> *tmp = BinTree<T>::root;
		BinTreeNode<T> *pretmp = tmp;
		int lc;
		while(tmp->data != vle)//vle is element of bst
		{
			pretmp = tmp;
			if(tmp->data > vle)
				tmp = tmp->lchild;
			else if(tmp->data < vle)
				tmp = tmp->rchild;
			else
				break;
		}
		if(pretmp->lchild == tmp)
			lc = 0;
		else if(pretmp->rchild == tmp)
			lc = 1;
		else//pretmp == tmp,imply the root is the node waited to removed.Because the root node does not input as the formal parameter.
			lc = 2;
		if(tmp->lchild == nullptr || tmp->rchild == nullptr)//it contains the situation:1.BST only have 1 node; 2. 2 node,lchild or rchild.
		{
			if(tmp->lchild == nullptr)//lchild == nullptr or both nullptr.
			{
				if(lc == 0)
					pretmp->lchild = tmp->rchild;
				else if(lc == 1)
					pretmp->rchild = tmp->rchild;
				else//pretmp == tmp,it means the root will be deleted,so need to change it.
					BinTree<T>::root = tmp->rchild;
			}
			else
			{
				if(lc == 0)
					pretmp->lchild = tmp->lchild;
				else if( lc == 1)
					pretmp->rchild = tmp->lchild;
				else
					BinTree<T>::root = tmp->lchild;
			}
		}
		else if(tmp->lchild != nullptr && tmp->rchild != nullptr)
		{

			BinTreeNode<T> *tp;
   /*          if(lc == 2)//if the node is the root. */
				// tp = BinTree<T>::root->rchild;
			/* else */
			tp = tmp->rchild;
			BinTreeNode<T> *rrc = tp;
			BinTreeNode<T> *pretp = tp;
			while(tp->lchild != nullptr)//seek for the first node in inorder.
			{
				pretp = tp;
				tp = tp->lchild;
			}
			// if(tp->rchild != nullptr)//if the first node have a rchild.
				pretp->lchild = tp->rchild;
		   /*  else */
				/* pretp->lchild = nullptr; */
			if(lc == 2)
				BinTree<T>::root = tp;
			else if( lc == 1)
				pretmp->rchild = tp;
			else
				pretmp->lchild = tp;
			tp->rchild = rrc;
			tp->lchild = tmp->lchild;
			delete tmp;
			tmp = nullptr;
		}
		return true;
	}
}

	template<typename T>
bool BSTree<T>::Remove(const T &vle,BinTreeNode<T> *&roo)
{
	BinTreeNode<T> *tmp;
	if(roo != nullptr)
	{
		if(roo->data > vle)
			Remove(vle,roo->lchild);
		else if(roo->data < vle)
			Remove(vle,roo->rchild);
		else if(roo->lchild != nullptr && roo->rchild != nullptr)
		{
			tmp = roo->rchild;
			while(tmp->lchild != nullptr)
				tmp = tmp->lchild;
			roo->data = tmp->data;
			Remove(roo->data,roo->rchild);
		}
		else
		{
			tmp = roo;
			if(roo->lchild == nullptr)
				roo = roo->rchild;
			else
				roo = roo->lchild;
			delete tmp;
			tmp = nullptr;
			return true;
		}
	}
	return false;
}

//-----------------------------AVLTree---------------------------------------------------
   /*  template<typename T> */
// bool AVLTree<T>::Insert(const T &vle)
// {
	// AVLTreeNode<T> *tmp = new AVLTreeNode<T>(vle);
	// AVLTreeNode<T> *roo = root;
	// while(roo != nullptr)
	// {
		// if(roo->data > vle)
		// {
			// if(roo->lchild != nullptr)
				// roo = roo->lchild;
			// else
				// break;
		// }
		// else if(roo->data < vle)
		// {
			// if(roo->rchild != nullptr)
				// roo = roo->rchild;
			// else
				// break;
		// }
		// else
		// {
			// std::cerr<<"repeating element.."<<std::endl;
			// return false;
		// }
	// }
	// if(vle > roo->data)
		// roo->rchild = tmp;
	// else
		// roo->lchild = tmp;
	// return true;
// }

	// template<typename T>
// bool AVLTree<T>::Search(const T &vle)
// {
	// if(root == nullptr)
	// {
		// std::cout<<"empty tree..."<<std::endl;
		// return false;
	// }
	// AVLTreeNode<T> *tmp = root;
	// while(tmp->data != vle)
	// {
		// if(tmp->data > vle && tmp->lchild != nullptr)
			// tmp = tmp->lchild;
		// else if(tmp->data < vle && tmp->rchild != nullptr)
			// tmp = tmp->rchild;
		// else
			// return false;
	// }
	// return true;
// }

	// template<typename T>
// bool AVLTree<T>::Remove(const T &vle,AVLTreeNode<T> *&roo)
// {
	// AVLTreeNode<T> *tmp;
	// if(roo != nullptr)
	// {
		// if(roo->data > vle)
			// Remove(vle,roo->lchild);
		// else if(roo->data < vle)
			// Remove(vle,roo->rchild);
		// else if(roo->lchild != nullptr && roo->rchild != nullptr)
		// {
			// tmp = roo->rchild;
			// while(tmp->lchild != nullptr)
				// tmp = tmp->lchild;
			// roo->data = tmp->data;
			// Remove(roo->data,roo->rchild);
		// }
		// else
		// {
			// tmp = roo;
			// if(roo->lchild == nullptr)
				// roo = roo->rchild;
			// else
				// roo = roo->lchild;
			// delete tmp;
			// tmp = nullptr;
			// return true;
		// }
	// }
	// return false;
// }

	// template<typename T>
// void AVLTree<T>::TraversePreOrder(AVLTreeNode<T> *ro,bool ingen)
// {
	// if(ingen == false)
	// {
		// if(ro == nullptr)
		// {
			// return;
		// }
		// else
		// {
			// std::cout<<ro->data<<" ";
			// TraversePreOrder(ro->lchild,ingen);
			// TraversePreOrder(ro->rchild,ingen);
			// return;
		// }
	// }
	// else
	// {
		// if(ro == nullptr)
		// {
			// return;
		// }
		// else
		// {
			// std::cout<<ro->data<<" ( ";
			// TraversePreOrder(ro->lchild,ingen);
			// std::cout<<",";
			// TraversePreOrder(ro->rchild,ingen);
			// std::cout<<" ) ";
			// return;
		// }

	// }
/* } */
   /*  template<typename T> */
// void AVLTree<T>::TraverseLevelOrder(AVLTreeNode<T> *roo)
// {
	// Queue<AVLTreeNode<T>*> q;
	// AVLTreeNode<T> *trav;
	// if(roo == nullptr)
	// {
		// std::cerr<<"empty tree,can not traverse"<<std::endl;
		// throw;
	// }
	// else
		// q.Enqueue(roo);
	// while(!q.IsEmpty())
	// {
		// q.Dequeue(trav);
		// std::cout<<trav->data<<" ";
		// if(trav->lchild != nullptr)
			// q.Enqueue(trav->lchild);
		// if(trav->rchild != nullptr)
			// q.Enqueue(trav->rchild);
	// }
// }

   /*  template<typename T> */
// size_t AVLTree<T>::height(AVLTreeNode<T> *roo)
// {
	// if(roo == nullptr)
		// return 0;
	// else
	// {
		// size_t i = Height(roo->lchild);
		// size_t j = Height(roo->rchild);
		// size_t height = i > j ? i + 1 : j + 1;
		// return height;
	// }
/* } */
//-----------------------------exclusive members of AVLTree-------------------
	template<typename T>
void AVLTree<T>::rotatel(AVLTreeNode<T> *roo)
{
	
}
#endif
