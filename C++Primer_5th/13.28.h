#include "comm.h"

class TreeNode
{
	public:
		std::string value;
		int *count;
		TreeNode *left;
		TreeNode *right;

	public:
		TreeNode(std::string s = std::string()):value(s),count(new int(1)),left(nullptr),right(nullptr){}
		TreeNode(const TreeNode &p):value(p.value),count(p.count),left(p.left),right(p.right){++*count;}
		TreeNode& operator=(const TreeNode &p)
		{
			++*p.count;
			if(--*count == 0)
			{
				if(left)
					delete left;
				if(right)
					delete right;
				delete count;
			}
			value = p.value;
			count = p.count;
			left = p.left;
			right = p.right;
			return *this;
		}
		~TreeNode()
		{
			if(--*count == 0)
			{
				if(left)
				{
					delete left;
					left = nullptr;
				}
				if(right)
				{
					delete right;
					right = nullptr;
				}
				delete count;
				count = nullptr;
			}
		}
};

class BinStrTree
{
	private:
		TreeNode *root;

	public:
		BinStrTree():root(new TreeNode()){}
		BinStrTree(const BinStrTree &p):root(p.root){}
		BinStrTree& operator=(const BinStrTree &p)
		{
			TreeNode *new_root = new TreeNode(*p.root);
			delete root;
			root = new_root;
			return *this;
				
		}
};
