#include "comm.h"

using namespace std;

int main()
{
	vector<int>a{1,2,3,4,5,5,6,7,8,7,7,7,9};
	sort(a.begin(),a.end());
	vector<int>b(a.size());
	unique_copy(a.begin(),a.end(),b.begin());
	for(auto i : b)
		cout<<i<<endl;
}
