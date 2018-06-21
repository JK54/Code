#include "comm.h"
using namespace std;

int main()
{
	vector<int> container;
	int tmp;
	while(cin>>tmp)
		container.push_back(tmp);
	auto ib = container.begin();
	auto ie = container.end() - 1;
	auto im = container.begin() + container.size()/2;
	while(ib<ie)
	{
		cout<<*ib + *ie<<endl;;
		ib++;
		ie--;
	}
	if(ib == ie)
		cout<<*ie<<endl;
	return 0;
}
