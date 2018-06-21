#include "comm.h"

using namespace std;
class StrBlobPtr;
class StrBlob {
private:
    shared_ptr<vector<string> > data;
    void check(string::size_type i, const string& msg) const
    {
	if (i >= data->size())
	    throw out_of_range(msg);
    }

public:
    friend class StrBlobPtr;
	StrBlob() : data(std::make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il);
    string::size_type size() { return data->size(); }
    bool empty() { return data->empty(); }

    void push_back(const string& str) { data->push_back(str); }

    string& front()
    {
	check(0, "front on empty StrBlob");
	return data->front();
    }
    string& back()
    {
	check(0, "back on empty StrBlob");
	return data->back();
    }
    const string& front() const
    {
	check(0, "front on empty StrBlob");
	return data->front();
    }
    const string& back() const
    {
	check(0, "back on empty StrBlob");
	return data->back();
    }
    StrBlobPtr begin();
    StrBlobPtr end();
};

class StrBlobPtr {
public:
    StrBlobPtr(): curr(0){}
    StrBlobPtr(StrBlob& a, size_t sz = 0)
	: wptr(a.data)
	, curr(sz)
    {
    }
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
    string deref() const;
    StrBlobPtr& incr();

private:
    shared_ptr<vector<string> > check(size_t, const string&) const;
    weak_ptr<vector<string> > wptr;
    size_t curr;
};

StrBlobPtr StrBlob::begin() 
{ 
	return StrBlobPtr(*this); 
}

StrBlobPtr StrBlob::end() 
{ 
	return StrBlobPtr(*this, data->size()); 
}
shared_ptr<vector<string>> StrBlobPtr::check(size_t i,const string &msg)const
{
	auto ret = wptr.lock();
	if(!ret)
		throw runtime_error("unbound StrBlobPtr");
	if(i >= ret->size())
		throw out_of_range(msg);
	return ret;
}

string StrBlobPtr::deref() const
{
	auto p = check(curr,"curr invalid");
	return (*p)[curr];
}
    
StrBlobPtr& StrBlobPtr::incr()
{
	check(curr,"reach the end of StrBlobPtr");
	++curr;
	return *this;
}
