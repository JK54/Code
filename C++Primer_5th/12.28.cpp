#include "comm.h"

using namespace std;

class TextQuery
{
	public:
		friend vector<string> build_line_string(ifstream &in_file);
		friend void build_map_string(vector<string> &line_string,set<size_t> &line_num,map<string,set<size_t>> &map_string);
	private:
		vector<string> line_string;
		set<size_t> line_num;
		map<string,set<size_t>> map_string;

};

class Query_Result
{
	public:
		friend class TextQuery;
		friend  map<string,set<size_t>>::const_iterator query_string( const map<string,set<size_t>> &map_string,const vector<string> & line_string,string query_word);

};
vector<string> build_line_string(ifstream &in_file)
{
	string line;
	vector<string>line_string;
	while(getline(in_file,line))
		line_string.push_back(line);
	return line_string;
}

void build_map_string(vector<string> &line_string,set<size_t> &line_num,map<string,set<size_t>> &map_string)
{
	string word;
	for(size_t i = 1;i <= line_string.size();++i)
	{
		istringstream in_string(line_string[i - 1]);
		while(in_string>>word)
		{
			for(auto i : word)
				if(isupper(i))
					i = tolower(i);
			word.erase(remove_if(word.begin(),word.end(),[](char a){return ispunct(a);}),word.end());
			map_string[word].insert(i);
			line_num.insert(i);
		}
	}
}
map<string,set<size_t>>::const_iterator query_string( const map<string,set<size_t>> &map_string,const vector<string> & line_string,string query_word)
{
	auto k = map_string.end();
	if(query_word.size() != 0)
	{
		k = map_string.find(query_word);
		if(k != map_string.end())
		{
			for(auto i :  k->second)
				cout<<"line "<<i<<":"<<line_string[i - 1]<<endl;;
		}
	}
	return k;
}
int main()
{
	ifstream in_file("The Call Of The Wild.txt");
	map<string,set<size_t>> map_string;	
	set<size_t> line_num;
	string tmp;
	vector<string> line_string = build_line_string(in_file);
	build_map_string(line_string,line_num,map_string);
	cin>>tmp;
	query_string(map_string,line_string,tmp);
	return 0;
}
