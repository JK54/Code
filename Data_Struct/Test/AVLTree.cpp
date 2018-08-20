#include "../Include/AVLTree.hpp"
#include "../Include/RBTree.hpp"
#include "../Include/BSTree.hpp"
// #include "Avl.cpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 500000
#define CW 10

AVLTree<int> aaa;
std::ofstream sta("compare.log");
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
		aaa.Insert(a[i]);
	}
	aaa.PrintCount();
	gettimeofday(&s1,NULL);
	t1 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
	for(int i = N - 1;i >= 0;i--)
		aaa.Search(a[i]);
	gettimeofday(&s0,NULL);
	t2 = (1000.0*(s0.tv_sec - s1.tv_sec) + (s0.tv_usec - s1.tv_usec)/1000.0) / 1000.0;
	for(int i = 0; i < N;i++)
		aaa.Remove(a[i]);
	gettimeofday(&s1,NULL);
	t3 = (1000.0*(s1.tv_sec - s0.tv_sec) + (s1.tv_usec - s0.tv_usec)/1000.0) / 1000.0;
}

double add_row(double data[][3],int row)
{
	double result = 0;
	for(int i = 0;i < 3;i++)
		result += data[row][i];
	return result;
}

double add_col(double data[][3],int col,int n)
{
	double result = 0;
	for(int i = 0;i < n;i++)
		result += data[i][col];
	return result;
}
int main()
{
	double t[CW][3];
	double total = 0,in = 0,s = 0,r = 0;
	for(int i = 0;i < CW;i++)
	{
		test();
		t[i][0] = t1;
		t[i][1] = t2;
		t[i][2] = t3;
	}
	sta<<"\t\t\t\t\t\t\t\t\t\tAvlTree_Han"<<std::endl;
	sta<<"\t\t\t\t\t\t\t\t\t"<<N<<" nodes"<<std::endl;
	sta<<"\t\t"<<"Insert time(s)"<<"\t\t"<<"Search time(s)"<<"\t\t"<<"Remove time(s)"<<"\t\t"<<"Total  time(s)"<<std::endl;
	for(int i = 0;i < CW;i++)
		sta<<std::fixed<<std::setprecision(6)<<" "<<(i + 1)<<"\t\t\t"<<t[i][0]<<"\t\t\t"<<t[i][1]<<"\t\t\t"<<t[i][2]<<"\t\t\t"<<add_row(t,i)<<std::endl;
	sta<<std::endl;
	in = add_col(t,0,CW);
	s = add_col(t,1,CW);
	r = add_col(t,2,CW);
	total = in + s + r;
	sta<<std::fixed<<std::setprecision(6)<<" Total "<<"\t\t"<<in<<"\t\t\t"<<s<<"\t\t\t"<<r<<"\t\t\t"<<total<<std::endl;
	sta<<std::fixed<<std::setprecision(6)<<" Avg "<<"\t\t"<<static_cast<double>(in/CW)<<"\t\t\t"<<static_cast<double>(s/CW)<<"\t\t\t"<<static_cast<double>(r/CW)<<"\t\t\t"<<static_cast<double>(total/CW)<<"\t\t\t"<<"\n\n"<<std::endl;
	close(fd);
	delete [] a;
	return 0;
}
