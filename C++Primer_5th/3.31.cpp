#include "comm.h"

using namespace std;

int main()
{
	vector<int> a;
	for(int i = 0; i < 10; i++)
		a.push_back(i);
	for(auto j :a)
		cout<<j<<endl;
	auto b = a;
	for(auto k :b)
		cout<<k<<endl;
	return 0;
}
