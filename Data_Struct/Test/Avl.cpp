#include "../Include/avltree.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 10000
#include <iostream>
#include <fstream>

AVLTreeNode *root = nullptr;
std::ofstream sta("avl.log");
struct timeval s0,s1;
double t1,t2,t3;
int *a = new int[N];
int fd = open("/dev/urandom",O_RDONLY);

void test()
{
	gettimeofday(&s0,NULL);
	for(int i = 0;i < N;i++)
	{
		read(fd,&a[i],sizeof(int));
		Insert(a[i],root);
	}
	gettimeofday(&s1,NULL);
	t1 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0);
	for(int i = N - 1;i >= 0;i--)
		Search(a[i],root);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*(s0.tv_sec - s1.tv_sec) + (s0.tv_usec - s1.tv_usec)/1000.0);
	for(int i = 0; i < N;i++)
		Remove(a[i],root);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0);
}

int main()
{
	double t[10];
	double s = 0;
	for(int i = 1;i <= 10;i++)
	{
		test();
		t[i] = t1 + t2 + t3;
		sta<<i<<'\n'<<"Insert time : "<<t1<<" ms\n"<<"Search time : "<<t2<<" ms\n"<<"Remove time : "<<t3<<" ms\n"<<"Total  time : "<<t[i]<<" ms\n"<<std::endl;
		s += t[i];
	}
	sta<<"All cost : "<<(static_cast<int>(s / 1000)) << "s"<<(static_cast<int>(s) % 1000)<<" ms"<<std::endl;
	close(fd);
	delete [] a;
	return 0;
}
