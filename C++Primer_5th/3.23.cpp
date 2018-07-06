#include "comm.h"

using namespace std;

int main()
{
	vector<int> v1;
	int tmp;
	cout<<"input 10 nums."<<endl;
	for(int i = 0;i < 10;i++)
	{
		cin>>tmp;
		v1.push_back(tmp);
	}
	for(auto j = v1.cbegin();j != v1.cend();j++)
		cout<<*j<<"\x20";
	cout<<endl;
	for(auto k = v1.begin();k != v1.end();k++)
	{
		*k *= 2;
	}
	for(auto l:v1)
		cout<<l<<" ";
	cout<<endl;
	return 0;
}
