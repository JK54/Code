#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

int main()
{
	char ss[] = "We are Happy.";
	vector<char> str;
	int blankcount = 0,size = sizeof(ss) / sizeof(ss[0]);
	for(int i = 0;i < size - 1;i++)
	{
		str.push_back(ss[i]);
		if(ss[i] == ' ')
			blankcount++;
	}
	int asize = size + blankcount * 2;
	str.reserve(asize);
	for(int i = size,j = asize;i >= 0;i--)
	{
		if(str[i] != ' ')
			str[j--] = str[i];
		else
		{
			str[j--] = '0';
			str[j--] = '2';
			str[j--] = '%';
		}
	}
	for(int i = 0;i < asize;i++)
		cout<<str[i];
	cout<<endl;
	return 0;
}
