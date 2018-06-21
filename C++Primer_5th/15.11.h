#include "comm.h"

class Quote
{
	public:
		Quote() = default;
		Quote(const std::string &book,double sales_price):bookNo(book),price(sales_price){}
		std::string isbn() const {return bookNo;}

		virtual double net_price(std::size_t n) const { return n*price;}
		virtual void debug(){std::cout<<isbn()<<" "<<price<<std::endl;}
		virtual ~Quote() = default;

	private:
		std::string bookNo;
	protected:
		double price = 0.0;
};


class Bulk_quote:public Quote
{
	public:
		Bulk_quote() = default;
		Bulk_quote(const std::string &s1,double d1,std::size_t n,double d2):Quote(s1,d1),min_qty(n),discount(d2){}
		virtual void debug() override{std::cout<<isbn()<<" "<<price<<" "<<min_qty<<" "<<discount<<std::endl;} 
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

double print_total(std::ostream &os,const Quote &item,size_t n)
{
	double ret = item.net_price(n);
	os<<item.isbn()<<" "<<n<<" "<<ret<<std::endl;
	return ret;
}

