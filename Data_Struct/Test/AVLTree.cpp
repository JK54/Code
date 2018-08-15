#include "../Include/AVLTree.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 1000000
int main()
{
	AVLTree<int> aaa;
	std::ofstream sta("avl.log");
/*
 * #if DEBUG
 *     std::ifstream op("11.txt");
 * #else 
 *     std::ofstream ip("11.txt");
 * #endif
 */
	struct timeval s0,s1;
	long  t1,t2,t3;
	int *a = new int[N];
	int fd = open("/dev/urandom",O_RDONLY);
	gettimeofday(&s0,NULL);
	for(int i = 0;i < N;i++)
	{
// #ifndef DEBUG
		read(fd,&a[i],sizeof(int));
		while(aaa.Search(a[i]))
			read(fd,&a[i],sizeof(int));
		// ip<<a[i]<<" ";
		// ip.flush();
/*
 * #else
 *         op>>a[i];
 * #endif
 */
		aaa.Insert(a[i]);
	}
	gettimeofday(&s1,NULL);
	t1 = s1.tv_sec - s0.tv_sec;
	close(fd);
	aaa.PrintCount();
	for(int i = N - 1;i >= 0;i--)
		aaa.Search(a[i]);
	gettimeofday(&s0,NULL);
	t2 = s0.tv_sec - s1.tv_sec;
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
	gettimeofday(&s1,NULL);
	t3 = s1.tv_sec - s0.tv_sec;
	sta<<"Insert time : "<<t1<<'\n'<<"Search time : "<<t2<<'\n'<<"Remove time : "<<t3<<std::endl;
	delete [] a;
	return 0;
}
