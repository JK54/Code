#include "comm.h"

using namespace std;
void build_exp(ifstream &is,map<string,string> &convert_map)
{
	string key,value;
	while(is>>key&&getline(is,value))
	{
		if(value.size())
			convert_map.insert({key,value});
		else
			throw runtime_error("no rule for" + key);
	}
}

const string transform(const string &s,const map<string,string> &convert_map)
{
	const string default_s = "null";
	if(s.size())
	{
		if(convert_map.find(s) != convert_map.cend())
			return convert_map.find(s)->second;
		else
			throw runtime_error("no rule for input ");
	
	}
	else
		return default_s;
}


int main()
{
	map<string,string>convert_map;
	ifstream in_file("11.33.txt");
	build_exp(in_file,convert_map);
	string tmpstr;
	vector<string> tmp;
	/*
	 * while(cin>>tmpstr)
	 * {
	 *     tmpstr = transform(tmpstr,convert_map);
	 *     tmp.push_back(tmpstr);
	 * }
	 */
	// for(auto i : tmp)
		// cout<<i<<" "<<endl;
	for(auto i : convert_map)
		cout<<i.first<<" "<<i.second<<endl;

}
