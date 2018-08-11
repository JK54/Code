#include "../Include/RBTree.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define N 20000
int main()
{
	RBTree<int> aaa;
#if 1
	std::ofstream op("11.txt");
#else
	std::ifstream ip("11.txt");
#endif
	int *a = new int [N];
	int fd = open("/dev/urandom",O_RDONLY);
	for(int i = 0;i < N;i++)
	{
#if 1
		read(fd,&a[i],sizeof(int));
		while(aaa.Search(a[i]))
			read(fd,&a[i],sizeof(int));
		op<<a[i]<<" ";
#else
		ip>>a[i];
#endif
		aaa.Insert(a[i]);
	}
	close(fd);
	aaa.PrintCount();
	// std::cout<<aaa.IsRBT()<<std::endl;
	// aaa.Traverse();
	delete [] a;
	return 0;
}
