#include "comm.h"

using namespace std;
#define SIZE 1048
int main()
{
	vector<string> str;
	str.reserve(1024);
	string word;
	for(auto i = 0;i < SIZE;++i)
	{
		word = i;
		str.push_back(word);
	}
	cout<<str.size()<<"\t"<<str.capacity()<<endl;
	str.resize(str.size() + str.size()*2);
	cout<<str.size()<<"\t"<<str.capacity()<<endl;
}
