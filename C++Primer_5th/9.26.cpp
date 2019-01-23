#include "comm.h"

using namespace std;

int main()
{
	int ia[] = {0,1,1,2,3,5,8,13,21,34,55,89};
	for(auto i:ia)
		cout<<i<<" ";
	cout<<endl;
	vector<int> vec1(ia,ia+12);
	list<int> list1(ia,ia+12);
	for(auto i = vec1.begin();i != vec1.end();)
	{
		if(*i % 2 == 1 || *i == 0) 
			i = vec1.erase(i);
		else
			++i;
	}
	for(auto i = list1.begin();i != list1.end();)
	{
		if((*i % 2) == 0)
			i = list1.erase(i);
		else
			++i;
	}
	for(int i : vec1)
		cout<<i<<" ";
	cout<<endl;
	for(int i :list1)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
