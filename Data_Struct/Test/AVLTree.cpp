#include "../Include/AVLTree.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
	AVLTree<int> aaa;
#if 0
	std::ifstream op("11.txt");
#else 
	std::ofstream ip("11.txt");
#endif
	unsigned short a[30];
	int fd = open("/dev/urandom",O_RDONLY);
	int num = static_cast<int>(sizeof(a)/sizeof(a[0]));
	for(int i = 0;i < num;i++)
	{
#if 1 
		read(fd,&a[i],sizeof(unsigned short));
		a[i] = a[i] % (2 * num);
		while(aaa.Search(a[i]))
		{
			read(fd,&a[i],sizeof(unsigned short));
			a[i] = a[i] % (3 * num);
		}
		ip<<a[i]<<" ";
		ip.flush();
#else 
		op>>a[i];
#endif
		aaa.Insert(a[i]);
	}
	close(fd);
	for(int i = num - 1; i >= 0;i--)
	{
   /*      std::cout<<"preorder : "; */
		// aaa.TraversePreOrder(aaa.Root());
		// std::cout<<std::endl;
		// std::cout<<"inorder  : ";
		// aaa.TraverseInOrder(aaa.Root());
		// std::cout<<std::endl;
		// std::cout<<"levelord : ";
		// aaa.TraverseLevelOrder(aaa.Root());
		// std::cout<<std::endl;std::cout<<"wanted : "<<a[i]<<std::endl;
		aaa.Remove(a[i]);
		// std::cout<<"inorder  : ";
		// aaa.TraverseInOrder(aaa.Root());
		// std::cout<<std::endl;
		// std::cout<<"still remain : ";
		aaa.PrintCount();
		/* std::cout<<std::endl; */
	}
	return 0;
}
