#include "15.15.h"

using namespace std;

int main()
{
	// vector<shared_ptr<Quote>>basket;
	// basket.push_back(make_shared<Bulk_quote>("qwe",50,10,0.25));
	Bulk_quote i("qwe",50,10,0.25);
	cout<<i.net_price(15)<<endl;
	// cout<<basket.back()->net_price(15)<<endl;
}
