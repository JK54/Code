#include "comm.h"
#include <list>

int main()
{
		/*
		 * std::string a = "12345567789";
		 * std::string b = "asdfgj";
		 * char *c = a.begin();
		 * char *d = b.begin();
		 */
		std::list<const char*> list1{"1234","asdfg"};
		std::vector<std::string> str1;
		str1.push_back(*(list1.begin()));
		std::cout<<str1[0]<<std::endl;
}
