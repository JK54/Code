#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
	vector<string> vec1;
	string tmp;
	while(cin>>tmp)
		vec1.push_back(tmp);
	for(auto j : vec1)
		cout<<j<<""<<endl;
	for(auto j : vec1)
	{
		for(auto k : j)
		{
			if(islower(k))
				toupper(k);
			else
				continue;
		}
	}
	for(auto j : vec1)
		cout<<j<<""<<endl;
	return 0;
}

