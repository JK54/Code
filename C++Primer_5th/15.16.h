#include "15.15.h"

class Limit_quote:public Disc_quote
{
	public:
		Limit_quote() = default;
		Limit_quote(const std::string &s1,double d1,size_t n,double d2):Disc_quote(s1,d1,n,d2){}
		double net_price(size_t n) const  override
		{
			std::cout<<"Limit_quote version of net_price"<<std::endl;
			return n*price*(n>qty?1-discount:1);
		}

};
