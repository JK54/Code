#include<iostream>
#include<string>
using namespace std;

int main()
{
	string str;
	if(getline(cin,str))
	{
		string result;
		int j = 0;
		for(int i = 0;i < str.size();i++)
		{
			if(isspace(str[i]))
				continue;
			else
				result += str[i];
		}
		cout<<result<<endl;
		return 0;
	}
	else
		cout<<"input valid string!"<<endl;
}
