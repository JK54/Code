#include "comm.h"

using namespace std;

int main()
{
	vector<int> vec1{1,2,3,4,5,6,7,8,9,10};
	cout<<accumulate(vec1.begin(),vec1.end(),0)<<endl;
	return 0;
}
