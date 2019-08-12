#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;

void pa_sub(const string &str,int start,int end,int len,int &pastart,int &maxlen)
{
	for(int i = start,j = end,k;i >= 0 && j < len && str[i] == str[j];i--,j++)
		if((k = j - i + 1) > maxlen)
			maxlen = k,pastart = i;
}

string palindrome(const string &str)
{
	int len = str.length();
	int start = 0,maxlen = 0;
	for(int i = 0;i < len;i++)
	{
		pa_sub(str,i,i,len,start,maxlen);
		pa_sub(str,i,i + 1,len,start,maxlen);
	}
	if(maxlen > 0)
		return str.substr(start,maxlen);
	return "";
}

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		cout<<"didididid\n";
		return 1;
	}
	cout<<palindrome(argv[1])<<std::endl;
	return 0;
}
