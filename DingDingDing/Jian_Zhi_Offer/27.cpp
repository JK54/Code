#include <iostream>

#include "tree.h"

int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int ain[]  = {5,3,6,2,4,1,7,8,11,12,10,9};
	Tree a(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));
	a.traverse();
	a.reverse(a.root);
	a.traverse();
	a.reverse(a.root);
	a.traverse();
	return 0;
}
