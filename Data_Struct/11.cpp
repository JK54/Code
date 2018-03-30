#include "include/sys_comm.h"

using namespace std;

class aa
{
	public:
		int a;
		bool operator>(const aa &p){	return a>p.a;	}
};
int main()
{
	aa a,b;
	a.a = 1;
	b.a = 2;
	cout<<a.operator>(b)<<endl;
}
