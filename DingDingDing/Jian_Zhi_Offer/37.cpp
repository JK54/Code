#include <iostream>
#include <fstream>
#include "tree.h"

void serial(TreeNode *p,std::ostream &os)
{
	if(p == nullptr)
	{
		os<<"$,";
		return;
	}
	os<<p->key<<",";
	serial(p->lchild,os);
	serial(p->rchild,os);
}

bool readnum(std::istream &is,int &num)
{
	char sz;
	num = 0;
	while(is>>sz)
	{
		if(sz == '$')
		{
			is>>sz;
			return false;
		}
		if(sz == ',')
			break;
		num = num * 10 + (sz - '0');
	}
	return true;
}

void deserial(TreeNode **p,std::istream &is)
{
	int num;
	if(readnum(is,num))
	{
		*p = new TreeNode(num);
		std::cout<<(*p)->key<<std::endl;
		deserial(&((*p)->lchild),is);
		deserial(&((*p)->rchild),is);
	}
}

int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int ain[]  = {5,3,6,2,4,1,7,8,11,12,10,9};
	Tree a(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));
	std::ofstream os("37.txt");
	serial(a.root,os);
	os.close();
	std::ifstream is("37.txt");
	TreeNode *p;
	deserial(&p,is);
	Tree b;
	b.root = p;
	b.traverse();
	is.close();
	return 0;
}
