#include "comm.h"

using namespace std;

int main()
{
	vector<string> vec1{"Hello","eve","dota","bind","Hello"};
	cout<<count(vec1.begin(),vec1.end(),"Hello")<<endl;
	return 0;
}
