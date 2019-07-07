struct TreeNode
{
	int key;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
	explicit TreeNode(int x):key(x),lchild(nullptr),rchild(nullptr){}
};

struct Tree
{
	struct TreeNode *root;
	explicit Tree(int preo[],int ino[],int prelen,int inlen);
	Tree():root(nullptr){}
	~Tree();
	void traverse();
	void traverselevel();
	void traverselevelbylevel();
	void traverselevelzigzag();
	bool issub(struct Tree &b);
	void reverse(TreeNode *p);
	bool ismirror(struct Tree &b);

	private:

		void TraverseInOrder(struct TreeNode *p);
		void destroy(struct TreeNode *p);
		bool Sub(struct TreeNode *pa,struct TreeNode *pb);
		struct TreeNode* CreateTreePreInOrder(int preo[],int ino[],int len);
		bool mirror(TreeNode *pa,TreeNode *pb);
};

