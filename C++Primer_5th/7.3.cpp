#include "comm.h"
#include "7.2.h"

using namespace std;

int main()
{
		Sales_data total;
		if(std::cin>>total.bookNo>>total.units_sold>>total.revenue)
		{
				Sales_data trans;
				while(std::cin>>trans.bookNo>>trans.units_sold>>trans.revenue)
				{
						if(total.bookNo == trans.bookNo)
								total = total.combine(trans);
						else
						{
								cout<<total.bookNo<<"\t"<<total.units_sold<<"\t"<<total.revenue<<endl;
								total = trans;
						}
				}
				cout<<total.bookNo<<"\t"<<total.units_sold<<"\t"<<total.revenue<<endl;
		}
		else
		{
				std::cerr<<"No Data."<<endl;
				return -1;
		}
		return 0;
}
