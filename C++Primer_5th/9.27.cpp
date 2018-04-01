#include "comm.h"

using namespace std;

int main()
{
    array<int,12> arr1{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}};
	for(auto i:arr1)
		cout<<i<<" ";
	cout<<endl;
    forward_list<int> flst1(arr1.begin(),arr1.end());
	auto prev = flst1.before_begin();
	auto curr = flst1.begin();
	while(curr != flst1.end())
	{
		if(*curr % 2)
			curr = flst1.erase_after(prev);
		else
		{
			prev = curr;
			++curr;
		}
	}
	for(auto i:flst1)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
