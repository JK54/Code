#include "comm.h"

using namespace std;

int main()
{
	ifstream os("11.3.txt");
	map<string,int> word_count;
	string tmp;
	while(os>>tmp)
	{
		for(auto &e:tmp)
		{
			if(isupper(e))
				e = tolower(e);
			else if(ispunct(e))
				tmp.erase(remove_if(tmp.begin(),tmp.end(),[](char a){return ispunct(a);}),tmp.end());
		}
		auto ret = word_count.insert({tmp,1});
		if(!ret.second)
			++ret.first->second;
	}
	for(auto w:word_count)
		cout<<w.first<<":"<<w.second<<endl;
	return 0;

}
