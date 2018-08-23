#include "../Include/Treap.hpp"
#define N 50000
int main()
{
	Treap<int> aaa;
	for(int i = 1;i < N;i++)
		aaa.Insert(i);
	// aaa.Traverse(aaa.Root());
	std::cout<<std::endl;
	std::cout<<std::endl;
	for(int i = 1;i < N;i++)
		aaa.Remove(i);
	// aaa.Traverse(aaa.Root());
	return 0;
}
