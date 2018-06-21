#include "comm.h"

using namespace std;

string make_plural(int count,const string &a,const string & end)
{
	return (count>1)?a+end:a;
}

void elimDups(vector<string>& STR)
{
	sort(STR.begin(),STR.end());
	auto unique_end = unique(STR.begin(),STR.end());
	for(auto i:STR)
		cout<<i<<" ";
	cout<<endl;
	STR.erase(unique_end,STR.end());
	for(auto i:STR)
		cout<<i<<" ";
	cout<<endl;
}

void biggies(vector<string>words,vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(),words.end(),[](const string &a,const string &b){return a.size()<b.size();});
	auto fc = stable_partition(words.begin(),words.end(),[sz](const string &a){return a.size() < sz;});
	cout<<*fc<<endl;
	auto count = words.end() - fc;
	cout<<count<<" "<<make_plural(count,"word","s")<<" equal or longer than "<<sz<<endl;
	for_each(fc,words.end(),[](const string &s){cout<<s<<" ";});
	cout<<endl;
}

int main()
{
	vector<string> str{"qwert","asdfgh","zxcsdfd","asd","xxz","qwrty","qwer"};
	vector<string>::size_type sz = 5;
	biggies(str,sz);
	return 0;
}
