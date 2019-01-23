#include "comm.h"

using namespace std;

int main()
{
	ifstream in("10.29.txt");
	istream_iterator<string> str_it(in);
	istream_iterator<string> eof;
	ostream_iterator<string> os(cout," ");
	vector<string> str;
	while(str_it != eof)
		str.push_back(*str_it++);
	for(auto i:str)
		os = i;
	cout<<endl;
	return 0;
}
