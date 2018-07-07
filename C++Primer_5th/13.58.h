#include "comm.h"

class FOO
{
	public:
		FOO sorted() &&;
		FOO sorted() const &;
	private:
		std::vector<int> data;
};

FOO FOO::sorted() &&
{
	sort(data.begin(),data.end());
	std::cout<<"rrrrr"<<std::endl;
	return *this;
}

FOO FOO::sorted() const &
{
	FOO newe(*this);
	sort(newe.data.begin(),newe.data.end());
	std::cout<<"llllll"<<std::endl;
	return newe;
}
