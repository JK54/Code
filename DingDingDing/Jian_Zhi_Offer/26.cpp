#include <iostream>

#include "tree.h"

int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int ain[]  = {5,3,6,2,4,1,7,8,9,11,12,10};
	int bpre[] = {10,11,12};
	int bin[] = {11,12,10};
	Tree a(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));
	Tree b(bpre,bin,sizeof(bpre) / sizeof(bpre[0]),sizeof(bin) / sizeof(bin[0]));
	a.traverse();
	b.traverse();
	std::cout<<a.issub(b)<<std::endl;
	return 0;
}
