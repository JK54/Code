#include <iostream>

#include "tree.h"

int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int aino[] = {5,3,6,2,4,1,7,8,11,12,10,9};
	int bpre[] = {1,7,8,9,10,11,12,2,4,3,6,5};
	int bino[] = {9,10,12,11,8,7,1,4,2,6,3,5};
	int cpre[] = {1,7,8,9,10,11,12,2,4,3,6,5};
	int cino[] = {10,12,11,9,8,7,1,4,2,6,3,5};
	Tree a(apre,aino,sizeof(apre) / sizeof(apre[0]),sizeof(aino) / sizeof(aino[0]));
	Tree b(bpre,bino,sizeof(bpre) / sizeof(bpre[0]),sizeof(bino) / sizeof(bino[0]));
	Tree c(cpre,cino,sizeof(cpre) / sizeof(cpre[0]),sizeof(cino) / sizeof(cino[0]));
	a.traverse();
	b.traverse();
	c.traverse();
	std::cout<<a.ismirror(b)<<std::endl;
	std::cout<<a.ismirror(c)<<std::endl;
	std::cout<<b.ismirror(a)<<std::endl;
	std::cout<<b.ismirror(c)<<std::endl;
	std::cout<<c.ismirror(a)<<std::endl;
	std::cout<<c.ismirror(b)<<std::endl;
	std::cout<<std::endl;
	std::cout<<sizeof(TreeNode)<<'\t'<<sizeof(Tree)<<std::endl;
	return 0;
}
