#include "../Include/Splay_Tree.hpp"

int main()
{
	SpTree<int> aaa;
	for(int i = 1;i < 50000;i++)
		aaa.Insert(i);
	std::cout<<std::endl;
	for(int i = 1;i < 50000;i++)
		aaa.Search(i);
	for(int i = 1;i < 50000;i++)
		aaa.Remove(i);
	return 0;
}
