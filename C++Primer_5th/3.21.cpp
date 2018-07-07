#include "comm.h"

using namespace std;

int main()
{
	vector<int>v1;
	vector<int>v2(10);
	vector<int>v3(10,42);
	vector<int>v4{10};
	vector<int>v5{10,42};
	vector<string>v6{10};
	vector<string>v7{10,"hi"};
	vector<vector<int>>array1{v1,v2,v3,v4,v5};
	vector<vector<string>>array2{v6,v7};
	for(int i = 0;i < array1.size();i++)
	{
		for(auto k = array1[i].cbegin();k!=array1[i].cend();++k)
			cout<<*k<<endl;
	}
	for(int i = 0;i < array2.size();i++)
	{
		for(auto k:array2[i])
			cout<<k<<endl;
	}

	return 0;
}
