#include "comm.h"
using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;
using std::cin;

class Sales_data;
istream& read(istream& is, Sales_data& item);
class Sales_data {
    friend istream& read(istream& is, Sales_data& item);
    friend std::ostream& print(ostream& os, const Sales_data& item);
	friend istream& operator>>(istream& is, Sales_data& s);
    string bookNo;
    unsigned units_sold = 0;
    mutable double revenue = 0.0;

public:
    Sales_data(const string& s, unsigned n, double p)
	: bookNo(s)
	, units_sold(n)
	, revenue(p * n)
    {
    }
    Sales_data()
	: Sales_data("", 0, 0)
    {
	read(cin, *this);
    }
    Sales_data(istream& is) { read(is, *this); }
    Sales_data(const string& s)
	: bookNo(s)
    {
    }
    string isbn() const { return bookNo; };
    Sales_data& combine(const Sales_data&);
    inline double avg_price() const;
};

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
istream& read(istream& is, Sales_data& item)
{
    double price = 0;
    cout << "input isbn\tunits_sold\tprice" << endl;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}
std::ostream& print(ostream& os, const Sales_data& item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue;
    return os;
}
Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}
inline double Sales_data::avg_price() const
{
    return static_cast<double>((*this).revenue) / static_cast<double>(this->units_sold);
}
istream& operator>>(istream& is, Sales_data& s)
{
    double price;
    is >> s.bookNo >> s.units_sold >> price;
    s.revenue = price * s.units_sold;
    return is;
}

struct Person {
private:
    string name;
    string address;
    string getname() const { return name; };
public:
    auto getaddress() const -> string const& { return address; };
    friend istream& read(istream& is, Person& person);
    friend ostream& print(ostream& os, Person& person);
};

istream& read(istream& is, Person& person)
{
    cout << "input name\taddress" << endl;
    is >> person.name >> person.address;
    return is;
}

ostream& print(ostream& os, Person& person)
{
    cout << "name\taddress" << endl;
    os << person.name << person.address;
    return os;
}
class Screen;
class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);

private:
    std::vector<Screen> screens;
};

class Screen {
    friend void Window_mgr::clear(ScreenIndex);

public:
    typedef std::string::size_type pos;
    Screen() = default;
    Screen(pos ht, pos wd)
	: height(ht)
	, width(wd)
    {
    }
    Screen(pos ht, pos wd, char c)
	: height(ht)
	, width(wd)
	, contents(ht * wd, c)
    {
    }
    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const { return contents[r * width + c]; }
    Screen& move(pos r, pos c);
    Screen& set(char);
    Screen& set(pos, pos, char);
    Screen& display(ostream& os)
    {
	do_display(os);
	return *this;
    }
    const Screen& display(ostream& os) const
    {
	do_display(os);
	return *this;
    }

private:
    pos cursor = 0, height = 0, width = 0;
    string contents;
    void do_display(ostream& os) const { os << contents; }
};

Screen& Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

Screen& Screen::set(pos r, pos col, char c)
{
    contents[r * width + col] = c;
    return *this;
}
void Window_mgr::clear(ScreenIndex i)
{
    Screen& s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}
