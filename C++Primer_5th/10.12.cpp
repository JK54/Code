#include "comm.h"

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

int main()
{
    std::vector<std::string> str1{ "abc", "qwer", "asdf", "zxcv", "ghjhkjuno", "uiop", "bvcx", "lkjhg", "a" };
    std::vector<Sales_data> vec1;
    for (auto i : str1)
	vec1.push_back(i);
    // sort(vec1.begin(),vec1.end(),compareIsbn);
    stable_sort(vec1.begin(), vec1.end(), compareIsbn);
    for (auto i = vec1.begin(); i != vec1.end(); ++i)
	std::cout << (*i).isbn() << std::endl;
}
