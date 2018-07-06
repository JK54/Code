#include "comm.h"

using namespace std;

int main(int,char**argv)
{
	ifstream in(argv[1]);
	istream_iterator<int> is(in);
	istream_iterator<int> eof;
	ofstream out1(argv[2]);
	ofstream out2(argv[3]);
	ostream_iterator<int> oseven(out1," ");
	ostream_iterator<int> osodd(out2," ");
	while(is != eof)
	{
		if(*is %2 == 0)
			*osodd = *is;
		else
			*oseven = *is;
		++is;
	}
	return 0;
}
