#include "tree.cpp"

int main()
{
	int apre[] = {1,2,3,5,6,4,7,8,9,10,11,12};
	int ain[]  = {5,3,6,2,4,1,7,8,11,12,10,9};
	Tree a(apre,ain,sizeof(apre) / sizeof(apre[0]),sizeof(ain) / sizeof(ain[0]));

	a.TraversePreOrder(a.root);
	std::cout<<std::endl;
	a.TraversePreOrder();
	std::cout<<std::endl;
	std::cout<<std::endl;
	a.TraverseInOrder(a.root);
	std::cout<<std::endl;
	a.TraverseInOrder();
	std::cout<<std::endl;
	std::cout<<std::endl;
	a.TraversePostOrder(a.root);
	std::cout<<std::endl;
	a.TraversePostOrder();
	std::cout<<std::endl;
}
