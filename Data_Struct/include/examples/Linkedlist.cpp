#include "../LinearList_linked_list.h"

using namespace std;

int main()
{
	LinkedList<int> p;
	int x;
	for(int i = 0;i < 15; ++ i)
	p.push_back(i);
	for(int i = 0;i<100; ++i)
	{
		p.pop_forward(x);
		cout<<x<<endl;
	}
}
