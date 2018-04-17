#include "comm.h"

using namespace std;

int main()
{
	vector<int> scores;
	vector<string> fas;
	int tmp;
	cout<<"input scores!"<<endl;
	while(cin>>tmp)
	{
		scores.push_back(tmp);
		cout<<"input scores!"<<endl;
	}
//	for(auto i = scores.begin();i != scores.end();++i)
//	{
//		if(*i < 60 && *i >= 0)
//			fas.push_back("fail");
//		else if(*i >= 60 && *i < 75)
//			fas.push_back("low pass");
//		else if(*i >= 75 && *i <= 100)
//			fas.push_back("high pass");
//		else
//			fas.push_back("invalid scores");
//	}
	for(auto i = scores.begin();i != scores.end();++i)
		(*i < 60 && *i >= 0)?fas.push_back("fail"):(*i >= 60 && *i < 75)?fas.push_back("low pass"):(*i >= 75 && *i <= 100)?fas.push_back("high pass"):fas.push_back("invalid scores");
	for(auto i:scores)
		cout<<i<<"\x20";
	cout<<endl;
	for(auto j:fas)
		cout<<j<<"\x20";
	cout<<endl;
	return 0;
}
