#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::memset;

int gethash(char a)
{
	return a;
}

int firstuniquechar(char str[])
{
	int len = strlen(str);
	int pos = -1;
	if(str == nullptr || len == 0)
		return -1;
	int count[128];
	memset(count,0,sizeof(int) * 128);
	for(int i = 0;i < len;i++)
		count[gethash(str[i])]++;
	cout<<str<<endl;
	for(int i = 0;pos == -1 && i < len;i++)
	{
		int num = count[gethash(str[i])];
		cout<<num<<" ";
		if(num == 1)
			pos = i;
	}
	cout<<endl;
	cout<<str[pos]<<endl;
	return pos;
}

int main()
{
	char str[] = "abcdeff";
	firstuniquechar(str);
	
}
