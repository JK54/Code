#include "comm.h"

using namespace std;

int main()
{
	vector<int> vec1;
	istream_iterator<int> is(cin);
	istream_iterator<int> eof;
	ostream_iterator<int> os(cout," ");
	copy(is,eof,back_inserter(vec1));
	sort(vec1.begin(),vec1.end());
	unique_copy(vec1.begin(),vec1.end(),os);
	cout<<endl;
}
