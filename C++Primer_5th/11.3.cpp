#include "comm.h"

using std::map;
using std::set;
using std::string;
using std::vector;
using std::ifstream;
using std::istream_iterator;
using std::ostream_iterator;
using std::cin;
using std::cout;
using std::endl;

int main(int,char**argv)
{
	ifstream os(argv[1]);
	map<string,size_t> word_count;
	string tmp;
	while(os>>tmp)
		++word_count[tmp];
	for(auto i:word_count)
		cout<<i.first<<" occur "<<i.second<<endl;
	return 0;
}
