#include "../Include/RBTree.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 50000000
std::set<int> aaa;
std::ofstream sta("set.log");
double t1,t2,t3;
struct timeval s0,s1;
int *a = new int [N];
int fd = open("/dev/urandom",O_RDONLY);

void test()
{
	gettimeofday(&s0,NULL);
	for(int i = 0;i < N;i++)
	{
		read(fd,&a[i],sizeof(int));
		aaa.insert(a[i]);
	}
	gettimeofday(&s1,NULL);
	t1 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0)/1000.0;
	for(int i = N -1;i >= 0;i--)
		aaa.find(a[i]);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*(s0.tv_sec - s1.tv_sec) + (s0.tv_usec - s1.tv_usec)/1000.0)/1000.0;
	for(int i = 0;i < N;i++)
		aaa.erase(a[i]);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0)/1000.0;
}

int main()
{
	double t[10];
	double s = 0;
	for(int i = 1;i <= 10;i++)
	{
		test();
		t[i] = t1 + t2 + t3;
		sta<<i<<'\n'<<"Insert time : "<<t1<<"s\n"<<"Search time : "<<t2<<"s\n"<<"Remove time : "<<t3<<"s\n"<<"Total time : "<<t[i]<<"s\n"<<std::endl;
		s += t[i];
	}
	sta<<"All cost : "<<(static_cast<int>(s / 60)) <<"m"<<(static_cast<int>(s) % 60)<<"s"<<std::endl;
	close(fd);
	delete [] a;
	return 0;
}
