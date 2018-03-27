#include "comm.h"

using namespace std;

template<typename T>
ostream &print(ostream &os,const T &t)
{
	return os<<t;
}

template<typename T,typename... Args>
ostream &print(ostream &os,const T &t,Args&... rest)
{
	os<<t<<",";
	return print(os,rest...);
}
int main()
{
	string a = "a";
	string b = "ab";
	string c = "abc";
	print(cout,a,b,c);
}
