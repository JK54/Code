#include "comm.h"

using namespace std::placeholders;
using std::vector;
using std::cout;
using std::endl;
using std::list;
using std::copy;
void print(const list<int> & a)
{
	for(auto i:a)
		cout<<i<<" ";
	cout<<endl;
}
int main()
{
	vector<int>vec{1,2,3,4,5,6,7,8,9};
	list<int>list1,list2,list3;
	copy(vec.begin(),vec.end(),inserter(list1,list1.begin()));
	copy(vec.begin(),vec.end(),front_inserter(list2));
	copy(vec.begin(),vec.end(),back_inserter(list3));
	print(list1);
	print(list2);
	print(list3);
}
