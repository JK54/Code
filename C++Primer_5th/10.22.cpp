#include "comm.h"

using namespace std::placeholders;
using std::vector;
using std::cout;
using std::endl;
using std::string;

bool check_size(const string &a,const string::size_type sz)
{
	return a.size() <= sz;
}

int main()
{
	vector<string> str1{"qwer","asdfgg","zxcxvxc","qwe","zf"};
	cout<<count_if(str1.begin(),str1.end(),bind(check_size,_1,6))<<endl;
	return 0;
}
