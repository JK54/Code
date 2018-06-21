#include "15.3.h"

class Bulk_quote:public Quote
{
	public:
		Bulk_quote() = default;
		Bulk_quote(const std::string &s1,double d1,std::size_t n,double d2):Quote(s1,d1),min_qty(n),discount(d2){}
		double net_price(size_t n)const override
		{
			if(n>min_qty)
				return n*(1-discount)*price;
			else
				return n*price;
		}
	private:
		size_t min_qty = 0;
		double discount = 0.0;
};
