#ifndef _FPRODUCT_H
#define _FPRODUCT_H

#include <string>

class Product
{
	public:
		virtual ~Product(){}
		virtual std::string name() = 0;
};

#endif
