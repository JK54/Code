#include "comm.h"

using namespace std;

class StrBlob 
{
	shared_ptr<vector<string>> data;
	void check(string::size_type i,const string & msg) const {if(i >= data->size())throw out_of_range(msg);}
public:
	StrBlob();
	StrBlob(initializer_list<string> il);
	string::size_type size(){return data->size();}
	bool empty(){return data->empty();}

	void push_back(const string &str){data->push_back(str);}

	string &front(){check(0,"front on empty StrBlob");return data->front();}
	string &back(){check(0,"back on empty StrBlob");return data->back();}
	const string &front() const {check(0,"front on empty StrBlob");return data->front();}
	const string &back() const {check(0,"back on empty StrBlob");return data->back();}

};

