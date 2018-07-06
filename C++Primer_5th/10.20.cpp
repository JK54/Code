#include "comm.h"

using namespace std;

int main()
{
	vector<string> str1{"qwer","asdfgg","zxcxvxc","qwe","zf"};
	cout<<count_if(str1.begin(),str1.end(),[](string &a){return a.size()>=6;})<<endl;
}
