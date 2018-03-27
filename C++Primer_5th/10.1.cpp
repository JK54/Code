#include "comm.h"

using namespace std;

int main()
{
	vector<int> vec1{1,2,3,4,5,6,245,4324,546,234,134,54,7,8,9,7,6,5,4,3,5,4,6,6,8,4,6,4,4,6,2352};
	cout<<count(vec1.begin(),vec1.end(),5)<<endl;
	return 0;
}
