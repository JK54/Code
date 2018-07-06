#include "comm.h"

using namespace std;

int main()
{
	vector<int>a{1,2,3,4,5,6,7,8};
	ostream_iterator<int>os(cout," ");
	for(auto i = a.crbegin(); i != a.crend(); ++i)
		os = *i;
	cout<<endl;
}
