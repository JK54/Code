#include <iostream>
#include <sstream>
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

int firstuniquechar(std::stringstream &is)
{
	int count[128];
	char ban;
	char fu;
	int index = -1;
	for(int i = 0;i < 128;i++)
		count[i] = -1;
	while(is>>ban)
	{
		index++;
		int pos = gethash(ban);
		if(count[pos] == -1)
			count[pos] = index;
		else if(count[pos] >= 0)
			count[pos] = -2;
	}
	index = -1;
	for(int i = 0;i < 128;i++)
	{
		if(count[i] > 0 && (index == -1 || index > count[i]))
		{
			index = count[i];
			fu = i;
		}
	}
	cout<<index<<":"<<fu<<endl;
	return index;
}

int gethash2(char a)
{
	return a - 'a';
}

int delpattern(char *str,char *pattern)
{
	if(str == nullptr || pattern == nullptr)
		return 0;
	cout<<str<<endl;
	int cc[26];
	int start,end;
	memset(cc,0,sizeof(int) * 26);
	while(*pattern != '\0')
		cc[gethash2(*(pattern++))]++;
	start = end = 0;
	while(str[end] != '\0')
	{
		while(str[end] != '\0' && cc[gethash2(str[end])] != 0)
			end++;
		if(start != end)
			str[start] = str[end];
		start++,end++;
	}
	memset(str + start,'\0',sizeof(char) * (end - start));
	cout<<str<<endl;
	cout<<end-start<<endl;
	return end - start;
}

int main()
{
	char str[] = "abc1deffb";
	// char pattern[] = "afbcde";
	// delpattern(str,pattern);
	// firstuniquechar(str);
	std::stringstream is;
	is<<str;
	firstuniquechar(is);
	return 0;	
}
