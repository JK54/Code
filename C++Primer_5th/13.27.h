#include "comm.h"

class HasPtr_ptr
{
	public:
		HasPtr_ptr() = default;
		HasPtr_ptr(const std::string &s = std::string()):ps(new std::string(s)),i(0),use(new std::size_t(1)){}
		HasPtr_ptr(const HasPtr_ptr &p):ps(p.ps),i(p.i),use(p.use){++*use;}
		HasPtr_ptr &operator=(const HasPtr_ptr &p)
		{
			++*p.use;
			if(--*use == 0)
			{
				delete ps;
				delete use;
			}
			ps = p.ps;
			i = p.i;
			use = p.use;
			return *this;
		}
		~HasPtr_ptr()
		{
			if(--*use == 0)
			{
				delete ps;
				delete use;
			}
		}
	private:
		std::string *ps;
		int i;
		std::size_t *use;
};
