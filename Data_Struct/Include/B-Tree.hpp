#include "sys_comm.h"

//the 2-3-4 B-Tree.	

template<typename T>
struct BTNode
{
	T data;
	BTNode<T> *parent;
	BTNode<T> *brother;
	BTNode<T> *child;//first children.
};

template<typename T>
class BTree
{
	public:
		BTree();
		~BTree();
	private:
		BTNode<T> *root;

};
