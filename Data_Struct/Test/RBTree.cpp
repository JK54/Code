#include "../Include/RBTree.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 1000000

int main()
{
	RBTree<int> aaa;
	std::ofstream sta("rbtree.log");
	int t1,t2,t3;
	struct timeval s0,s1;
/*
 * #ifndef DEBUG
 *     std::ofstream op("11.txt");
 * #else
 *     std::ifstream ip("11.txt");
 * #endif
 */
	int *a = new int [N];
	int fd = open("/dev/urandom",O_RDONLY);
	gettimeofday(&s0,NULL);
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
	gettimeofday(&s1,NULL);
	t1 = s1.tv_sec - s0.tv_sec;
	// std::cout<<aaa.IsRBT()<<std::endl;
	aaa.PrintCount();
	// aaa.Traverse();
	for(int i = N -1;i >= 0;i--)
	{
		aaa.Search(a[i]);
	}
	gettimeofday(&s0,NULL);
	t2 = s0.tv_sec - s1.tv_sec;
	for(int i = 0;i < N;i++)
	{
		aaa.Remove(a[i]);
		// std::cout<<aaa.IsRBT()<<std::endl;
	}
	gettimeofday(&s1,NULL);
	t3 = s1.tv_sec - s0.tv_sec;
	aaa.PrintCount();
	sta<<"Insert time : "<<t1<<'\n'<<"Search time : "<<t2<<'\n'<<"Remove time : "<<t3<<std::endl;
	delete [] a;
	return 0;
}
