#include "comm.h"
#include <random>
#include <ctime>
using namespace std::placeholders;
using std::vector;
using std::cout;
using std::endl;
using std::string;

bool check_size(const string &a,const string::size_type sz)
{
	return a.size() <= sz;
}

int main()
{
	vector<string> str1{"qwer","asdfgg","zxcxvxc","qwe","zf","l","qwertyui","asdfghjkl"};
	stable_sort(str1.begin(),str1.end(),[](const string &a,const string &b){return a.size() < b.size();});
	srand(time(NULL));
	string STR = str1[rand()%str1.size()];
	cout<<STR<<endl;

	vector<int> vec1{4,2,5,8,3,6,1,0,8,6,9,3,2,1,4,7,8,1,2,5,8,4};
	sort(vec1.begin(),vec1.end());
	auto iter = unique(vec1.begin(),vec1.end());
	vec1.erase(iter,vec1.end());
	
	// cout<<*find(vec1.begin(),vec1.end(),STR.size())<<endl;
	auto it = find_if(vec1.begin(),vec1.end(),bind(check_size,STR,_1));
	cout<<*it<<endl;
	return 0;
}
