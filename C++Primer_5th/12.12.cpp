#include "comm.h"

using namespace std;

void process(shared_ptr<int> ptr)
{
	*ptr = 1;
}

int main()
{
	auto p =new int();
	process(shared_ptr<int>(p));
	cout<<*p<<endl;
}
