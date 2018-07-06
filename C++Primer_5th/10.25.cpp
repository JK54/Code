#include "comm.h"

using namespace std;

string make_plural(int count,const string &a,const string & end)
{
	return (count>1)?a+end:a;
}

bool check_size(const string &a,const string::size_type sz)
{
	return a.size() >= sz;
}
void elimDups(vector<string>& STR)
{
	sort(STR.begin(),STR.end());
	auto unique_end = unique(STR.begin(),STR.end());
	cout<<endl;
	STR.erase(unique_end,STR.end());
	cout<<endl;
}

void biggies(vector<string>words,vector<string>::size_type sz)
{
	elimDups(words);
	//elimDups首先将序列排序后，删除重复元素，再用stable_sort重新进行排序，这次排序考虑字符串的长度。
	stable_sort(words.begin(),words.end(),[](const string &a,const string &b){return a.size()<b.size();});
	auto fc = partition(words.begin(),words.end(),bind(check_size,std::placeholders::_1,sz));
	//partition函数对容器内容进行划分，返回谓词为true的最后一个元素的下一位迭代器
	auto count = fc - words.begin();
	cout<<count<<" "<<make_plural(count,"word","s")<<" equal or longer than "<<sz<<endl;
	for_each(words.begin(),fc,[](const string &s){cout<<s<<" ";});
	cout<<endl;
}

int main()
{
	vector<string> str{"qwert","asdfgh","zxcsdfd","asd","xxz","qwrty","qwer"};
	vector<string>::size_type sz = 5;
	biggies(str,sz);
	return 0;
}
