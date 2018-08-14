#include "../Include/RBTree.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define N 20000
int main()
{
	RBTree<int> aaa;
/*
 * #ifndef DEBUG
 *     std::ofstream op("11.txt");
 * #else
 *     std::ifstream ip("11.txt");
 * #endif
 */
	int *a = new int [N];
	int fd = open("/dev/urandom",O_RDONLY);
	for(int i = 0;i < N;i++)
	{
// #ifndef DEBUG
		read(fd,&a[i],sizeof(int));
		while(aaa.Search(a[i]))
			read(fd,&a[i],sizeof(int));
/*
 *         op<<a[i]<<" ";
 * #else
 *         ip>>a[i];
 * #endif
 */
		aaa.Insert(a[i]);
	}
/*
 * #ifndef DEBUG
 *     op.flush();
 * #endif
 */
	close(fd);
	std::cout<<aaa.IsRBT()<<std::endl;
	aaa.PrintCount();
	// aaa.Traverse();
	for(int i = 0;i < N;i++)
	{
		aaa.Remove(a[i]);
		// std::cout<<aaa.IsRBT()<<std::endl;
	}
	aaa.PrintCount();
	delete [] a;
	return 0;
}
