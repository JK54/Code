#include "../Include/AVLTree.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define N 10000000
int main()
{
	AVLTree<int> aaa;
/*
 * #if 0
 *     std::ifstream op("11.txt");
 * #else 
 *     std::ofstream ip("11.txt");
 * #endif
 */
	int *a = new int[N];
	int fd = open("/dev/urandom",O_RDONLY);
	for(int i = 0;i < N;i++)
	{
		read(fd,&a[i],sizeof(int));
		while(aaa.Search(a[i]))
			read(fd,&a[i],sizeof(int));
		/*
		 * ip<<a[i]<<" ";
		 * ip.flush();
		 * op>>a[i];
		 */
		aaa.Insert(a[i]);
	}
	close(fd);
	aaa.PrintCount();
	for(int i = 0; i < N;i++)
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
		// aaa.PrintCount();
		/* std::cout<<std::endl; */
	}
	aaa.PrintCount();
	delete [] a;
	return 0;
}
