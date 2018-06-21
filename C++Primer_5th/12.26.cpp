#include"comm.h"

using namespace std;

int main()
{
	allocator<int> a;
	int* const p = a.allocate(10);
	int ps;
	int  * pp = p;
	while(cin>> ps && p != p + 10)
	{
		a.construct(pp++,ps);
	}
	while( pp >= p)
	{
		cout<<*pp<<endl;
		a.destroy(pp);
		--pp;
	}
	a.deallocate(p,10);
	return 0;
}
