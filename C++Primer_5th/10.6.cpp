#include "comm.h"

using namespace std;

int main()
{
	vector<int>vec1{1,2,3,4,5,6,7,8,9};
	fill_n(vec1.begin(),vec1.size(),0);
	for(auto i:vec1)
		cout<<i<<endl;
	return 0;
}
