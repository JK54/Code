#include "comm.h"

using namespace std;

int main()
{
	string tmp;
	vector<string> procession;
	while(getline(cin,tmp))
		procession.push_back(tmp);
	auto i = procession.begin();
	if(i != procession.end())
	{
		for(auto j = i->begin();j != i->end();j++)
		{
			if(islower(*j))
				*j = toupper(*j);
		}
	}
	cout<<*i<<endl;
//	for(auto k : procession)
//		cout<<k<<endl;
	return 0;
}
