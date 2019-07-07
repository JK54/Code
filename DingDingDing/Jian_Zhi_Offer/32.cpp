#include <iostream>
#include "tree.h"

int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int ain[]  = {5,3,6,2,4,1,7,8,11,12,10,9};
	int bpre[] = {1,2,4,8,9,5,10,11,3,6,12,13,7,14,15};
	int bin[]  = {8,4,9,2,10,5,11,1,12,6,13,3,14,7,15};
	Tree a(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));
	Tree b(bpre,bin,sizeof(bpre) / sizeof(bpre[0]),sizeof(bin) / sizeof(bin[0]));
	a.traverse();
	a.traverselevel();	
	std::cout<<std::endl;
	a.traverselevelbylevel();	
	std::cout<<std::endl;
	a.traverselevelzigzag();
	std::cout<<std::endl;
	b.traverselevelzigzag();
}
