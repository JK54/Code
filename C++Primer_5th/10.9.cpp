#include "comm.h"

using namespace std;


void elimDups(vector<string>& STR)
{
	sort(STR.begin(),STR.end());
	auto unique_end = unique(STR.begin(),STR.end());
	STR.erase(unique_end,STR.end());
}
int main()
{
	vector<string> vec1{"Hello","World","Hello","Morning"};
	elimDups(vec1);
	for(auto i :vec1)
		cout<<i<<endl;
	return 0;
}
