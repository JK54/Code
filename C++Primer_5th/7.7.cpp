#include "chapter7.h"

int main()
{
		Sales_data total;
		if(read(cin,total))
		{
				Sales_data trans;
				while(read(cin,trans))
				{
						if(total.isbn() == trans.isbn())
								total = add(total,trans);
						else
						{
								print(cout,total);
								cout<<endl;
								total = trans;
						}
						print(cout,total);
						cout<<endl;
				}
		}
				else
				{
						std::cerr<<"aaaaaaa"<<endl;
						return -1;
				}
				return 0;
}



