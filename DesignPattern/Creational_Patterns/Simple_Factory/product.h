#ifndef _SPRODUCT_H
#define _SPRODUCT_H

#include <string>

class Product
{
	public:
		virtual ~Product(){}
		virtual std::string name() = 0;
};

#endif
