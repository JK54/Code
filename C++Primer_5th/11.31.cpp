#include "comm.h"

using namespace std;

int main()
{
	multimap<string,string> authors;
	cout<<"enter author and writing"<<endl;
	string author, writing;
	cin>>author>>writing;
	for(;author != "null";cin>>author>>writing,cout<<"enter author and writing"<<endl)
	{
		authors.insert({author,writing});
	}
	for(auto w:authors)
		cout<<w.first<<":"<<w.second<<endl;
	cout<<"enter the author you want to erase"<<endl;
	cin>>author;
	size_t i = authors.count(author);
	multimap<string,string>::iterator ite = authors.find(author);
	while(i)
	{
		ite = authors.erase(ite);
		--i;
	}
	for(auto w:authors)
		cout<<w.first<<":"<<w.second<<endl;
	return 0;
}
