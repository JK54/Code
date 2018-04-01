#include "15.3.h"

using namespace std;
double print_total(ostream &os,const Quote &item,size_t n)
{
	double ret = item.net_price(n);
	os<<item.isbn()<<" "<<n<<" "<<ret<<endl;
	return ret;
}

