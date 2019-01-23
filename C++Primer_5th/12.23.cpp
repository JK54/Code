#include "comm.h"

using namespace std;

int main()
{
	char *ccs = new char[100];
	string a = "avc";
	string b = "bvc";
	string tmp = a + b;
	for(size_t i = 0;i < tmp.size();++i)
		ccs[i] = tmp[i];
	cout<<ccs<<endl;
	delete [] ccs;
}
