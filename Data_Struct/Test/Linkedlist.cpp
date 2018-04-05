#include "../Include/LinearList_linked_list.hpp"

using namespace std;

int main()
{
	LinkedList<int> p;
	int x;
	for(int i = 0;i < 15; ++ i)
	p.push_back(i);
	for(int i = 0;i<17; ++i)
	{
		p.pop_forward(x);
		cout<<x<<endl;
	}
}
