#include "comm.h"


int main()
{
		std::string tmp;
		std::deque<std::string> dq1;
		auto ite = dq1.begin();
		while(std::cin>>tmp)
				ite = dq1.insert(ite,tmp);
		std::cout<<"\n";
		for(auto i = dq1.begin();i != dq1.end();++i)
				std::cout<<*i<<std::endl;
		return 0;
}
