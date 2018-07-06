#include "comm.h"

using namespace std;

int main()
{
	vector<string>str;
	vector<int>vec;
	ifstream is("11.12.txt");
	vector<pair<string,int>>result;
	string tmp;
	while(getline(is,tmp))
	{
		string num;
		string instr;
		int inint;
		for(auto i = tmp.begin(); i != tmp.end();++i)
		{
			if(isspace(*i))
			{
				num = string(i+1,tmp.end());
				instr = string(tmp.begin(),i);
				inint = atoi(num.c_str());
				continue;
			}
		}
		// result.push_back(make_pair(instr,inint));
		// result.push_back(pair<string,int>(instr,inint));
		result.push_back({instr,inint});
	}
	for(auto &p : result)
		cout<<p.first<<" "<<p.second<<endl;
	return 0;
}
