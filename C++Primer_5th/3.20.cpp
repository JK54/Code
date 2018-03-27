#include "comm.h"
using namespace std;

int main()
{
	vector<int> container;
	int tmp;
	while(cin>>tmp)
		container.push_back(tmp);
	for(int i = 0 ; i < container.size()/2;i++)
	{
		tmp = container[i] + container[container.size() - 1 - i];
		cout<<tmp<<""<<endl;
	}
	if(container.size() % 2 != 0)
		cout<<container[container.size()/2]<<endl;
	return 0;
}
