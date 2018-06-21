#include "comm.h"

using namespace std;

int main()
{
	int i = 6;
	auto f = [i]()mutable->bool{ while(i > 0)--i;return i==0; };
	// auto f = [](int i)mutable->bool{ while(i > 0)--i;return i==0; };
	cout<<i<<" "<<f()<<endl;
}
