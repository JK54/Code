#include "comm.h"

class String 
{
	public:
		String():strb(nullptr),stre(nullptr){std::cout<<"String()"<<std::endl;}
		String(const std::string &);
		String(const String &);
		String& operator =(const String &);
		~String();
		
		size_t size() const {return stre - strb;}
		std::string* begin(){return strb;}
		std::string* end(){return stre;}
		// void push_back(const std::string &p);
	private:
		static std::allocator<std::string> alloc;
		std::string *strb;
		std::string *stre;
		std::string *strc;
		void reallocate();
		void free();
};

/*
 * String::String(char *a)
 * {
 *     std::string::size_type a_size = 0;
 *     char *tmp = a;
 *     while(*tmp != '\0')
 *     {
 *         ++a_size;
 *         ++tmp;
 *     }
 *     strb = stre = alloc.allocate(a_size);
 *     strc = strb + a_size;
 *     tmp = a;
 *     while(*tmp != '\0')
 *     {
 *         alloc.construct(stre++,*tmp);
 *     }
 *     std::cout<<"String(char *a)"<<std::endl;
 * }
 * 
 */
String::String(const std::string &s)
{
	auto ss = alloc.allocate(s.size()+1);
	alloc.construct(ss,s);
	strb = ss;
	stre = strc = strb + 1;
	std::cout<<"String(const std::string &)"<<std::endl;
}

String::String(const String &p)
{
	auto ib = alloc.allocate(p.strc - p.strb);
	auto ie = uninitialized_copy(p.strb,p.stre,ib);
	strb = ib;
	stre = ie;
	strc = ib; 
	std::cout<<"String(const String &)"<<std::endl;
}

String& String::operator=(const String &a)
{
	auto newa(a);
	free();
	strb = newa.strb;
	stre = newa.stre;
	strc = newa.strc;
	std::cout<<"operator="<<std::endl;
	return *this;
}
void String::free()
{
	if(strb)
	{
		for(auto s = stre; s != strb;)
		{
			alloc.destroy(--s);
		}
	}
	alloc.deallocate(strb,strc - strb);
}

String::~String()
{
	free();
}
void String::reallocate()
{
	auto new_size = size()?2*size():1;
	auto new_string = alloc.allocate(new_size);
	auto dest = new_string;
	auto source = strb;
	for(size_t i = 0 ; i != size();++i)
		alloc.construct(dest++,std::move(*source++));
	free();
	strb = new_string;
	stre = dest;
	strc = strb + new_size;
}

/*
 * void String::push_back(const std::string &str)
 * {
 *     while(str.size()>(strc - stre))
 *         reallocate();
 *     alloc.construct(stre++,std::move(str));
 * }
 */
