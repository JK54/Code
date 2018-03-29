#include "include/sys_comm.h"

using namespace std;

int* ff(int *a)
{
	return a;
}
int main()
{
	int a = 5,c = 6;
	int *b = &a;
	int *d = &c;
	ff(b) = d;
	cout<<*b<<endl;
}
