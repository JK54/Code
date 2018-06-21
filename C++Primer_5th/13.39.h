#include "comm.h"

class StrVec
{
	public:
		StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
		StrVec(const std::initializer_list<std::string> &);
		StrVec(const StrVec&);//
		StrVec& operator=(const StrVec&);//
		~StrVec();//

		void push_back(const std::string &);
		size_t size(){return first_free - elements;}
		size_t capacity(){return cap - elements;}
		void reserve(size_t n);
		void resize(size_t n);
		std::string *begin() const {return elements;}
		std::string *end() const {return first_free;}
		void print();
	private:
		static std::allocator<std::string> alloc;
		std::string *elements;
		std::string *first_free;
		std::string *cap;

		void chk_n_alloc(){if(size() == capacity()) reallocte();}//
		std::pair<std::string*,std::string*>alloc_n_copy(const std::string*,const std::string*);//
		void free();//
		void reallocte();//
};

std::allocator<std::string>StrVec::alloc;

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++,s);
}

std::pair<std::string*,std::string*> StrVec::alloc_n_copy(const std::string* b,const std::string* e)
{
	auto data = alloc.allocate(e - b);
	return {data,uninitialized_copy(b,e,data)};
}

void StrVec::free()
{
	if(elements)
		for(auto p = first_free; p != elements;)
			alloc.destroy(--p);//把--p放到这里而不是循环控制中，可以使代码简洁，判断条件更好进行处理
	alloc.deallocate(elements,cap - elements);
}

StrVec::StrVec(const StrVec & s4)
{
	auto newdata = alloc_n_copy(s4.begin(),s4.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(const std::initializer_list<std::string> &vs)
{
	first_free = elements = alloc.allocate(vs.size());
	cap = elements + vs.size();
	for(auto i : vs)
	{
		this->push_back(i);
	}
	for(auto i = elements; i != first_free; ++i)
		std::cout<<*i<<std::endl;
}
StrVec::~StrVec()
{
	free();
}

StrVec& StrVec::operator=(const StrVec &sccc)
{
	auto newdata(sccc);
	free();
	elements = newdata.elements;
	first_free = newdata.first_free;
	cap = newdata.cap;
	return *this;
}

void StrVec::reallocte()
{
	auto newcapacity = size()?size()*2:1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto source = elements;
	for(auto f = elements;f!= first_free; ++f)
	{
		alloc.construct(dest++,std::move(*source++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}


void StrVec::resize(size_t n)
{
	if(n <= capacity())
	{
		if(n >size())
		{
			for(size_t tmp = n - size(); tmp != 0; --tmp)
				this->push_back("");
		}
	}
	else
	{
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto source = elements;
		for(auto f = elements;f != first_free;)
			alloc.construct(dest++,std::move(*source++));
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + n;
	}
}

void StrVec::reserve(size_t n)
{
	if(n > capacity())
	{
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto source = elements;
		for(auto f = elements; f != first_free;)
			alloc.construct(dest++,std::move(*source++));
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + n;
	}
}

void StrVec::print()
{
	for(auto i = begin(); i != end(); ++i)
		std::cout<<*i<<" ";
	std::cout<<std::endl;
}
