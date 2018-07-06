#include "comm.h"

using namespace std;

class Sales_data {
public:
    std::string isbn() const { return BookNo; }
    Sales_data(std::string a)
	: BookNo(a)
    {
    }

private:
    std::string BookNo;
};

bool compareIsbn(const Sales_data& S1, const Sales_data& S2)
{
    return S1.isbn().size() < S2.isbn().size();
}
