#include "comm.h"

using namespace std;

bool compareS(const string &a)
{
	return a.size() <5;
}

int main()
{
	vector<string> words{"qwert","qwer","asdfg","zxcvb","asdf","zxcv","bnm"};
	auto i = partition(words.begin(),words.end(),compareS);
	while(i != words.end())
	{
		cout<<*i<<endl;
		++i;
	}
	return 0;
}
