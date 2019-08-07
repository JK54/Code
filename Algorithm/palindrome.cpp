#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

string palindrome(string str)
{
	int len = str.length();
	int start = 0,maxlen = 0;
	bool odd = len % 2;
	for(int i = 0;i < len;i++)
	{
		for(int substart = odd ? i - 1 : i,subend = i + 1;substart >= 0 && subend < len && str[substart] == str[subend];substart--,subend++)
		{
			int tmplen = subend - substart + 1;
			if(tmplen > maxlen)
			{
				maxlen = tmplen;
				start = substart;
			}
		}
	}
	if(maxlen > 0)
		return str.substr(start,start + maxlen);
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
