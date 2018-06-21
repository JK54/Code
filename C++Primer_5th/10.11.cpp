#include "comm.h"

using namespace std;

bool isShorter(const string &a,const string &b)
{
	return a.size() < b.size();
}
void elimDups(vector<string>& STR)
{
	sort(STR.begin(),STR.end());
	auto unique_end = unique(STR.begin(),STR.end());
	for(auto i:STR)
		cout<<i<<" ";
	cout<<endl;
	STR.erase(unique_end,STR.end());
	for(auto i:STR)
		cout<<i<<" ";
	cout<<endl;
}
int main()
{
	vector<string> vec1{"Hello","asfsdfsfgsdsdf","World","Hello","Morning","dsfsdfsdf","fox"};
	elimDups(vec1);
	stable_sort(vec1.begin(),vec1.end(),isShorter);
	for(auto i:vec1)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}
