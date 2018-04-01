#include "comm.h"

class Quote {
public:
    Quote(const std::string& s1)
	: bookNo(s1)
    {
	std::cout << "default cons" << std::endl;
    };
    Quote(const std::string& book, double sales_price)
	: bookNo(book)
	, price(sales_price)
    {
	std::cout << "3 para cons" << std::endl;
    }
    Quote(Quote&& q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) { std::cout << "move cons" << std::endl; }
    bool operator!=(const Quote& rhs)
    {
	return this->bookNo == rhs.bookNo && this->price == rhs.price;
    }
    Quote& operator=(const Quote& rhs)
    {
	if (*this != rhs) {
	    bookNo = rhs.bookNo;
	    price = rhs.price;
	}
	std::cout << "Quote: copy =() \n";

	return *this;
    }
    Quote& operator=(Quote&& rhs) noexcept
    {
	if (*this != rhs) {
	    bookNo = std::move(rhs.bookNo);
	    price = std::move(rhs.price);
	}
	std::cout << "Quote: move =!!!!!!!!! \n";

	return *this;
    }
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const
    {
	std::cout << "Quote version of net_price" << std::endl;
	return n * price;
    }
    virtual void debug() { std::cout << isbn() << " " << price << std::endl; }
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& s1, double d1, std::size_t n, double d2)
	: Quote(s1, d1)
	, qty(n)
	, discount(d2)
    {
	std::cout << discount << std::endl;
    }
    double net_price(size_t n) const = 0;

    size_t qty;
    double discount;
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& s1, double d1, std::size_t n, double d2)
	: Disc_quote(s1, d1, n, d2)
    {
    }
    // virtual void debug() override { std::cout << isbn() << " " << price << " " << min_qty << " " << discount << std::endl; }
    double net_price(size_t n) const override
    {
	if (n > qty) {
	    std::cout << "Disc_quote version of net_price" << std::endl;
	    return n * (1 - Disc_quote::discount) * price;
	} else {
	    std::cout << "Disc_quote version of net_price" << std::endl;
	    return n * price;
	}
    }

private:
	size_t min_qty;
	double discount;
};

double print_total(std::ostream& os, const Quote& item, size_t n)
{
    double ret = item.net_price(n);
    os << item.isbn() << " " << n << " " << ret << std::endl;
    return ret;
}
