#include "comm.h"
//HasPtr的类值版本
class HasPtr
{
	public:
		HasPtr(const std::string &s):ps(new std::string(s)),i(0){}
		HasPtr(const HasPtr &p):ps(new std::string(*p.ps)),i(p.i){}
		~HasPtr(){delete ps;}
		HasPtr& operator=(const HasPtr &p)
		{
			auto tmp = new std::string (*p.ps);
			delete ps;
			ps = tmp;
			i = p.i;
			return *this;
		}
		void swap(HasPtr &lhs,HasPtr &rhs)
		{
			using std::swap;
			swap(lhs.ps,rhs.ps);
			swap(lhs.i,rhs.i);
			std::cout<<"HasPtr swap running"<<std::endl;
		}
			HasPtr& operator==(HasPtr q)
		{
			swap(*this,q);
			return *this;
		}
private:
		std::string *ps;
		int i;
};
