#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <string>

class ProductA
{
	public:
		virtual ~ProductA(){}
		virtual std::string name() = 0;
		virtual int property1() = 0;
};

class ProductB
{
	public:
		virtual ~ProductB(){}
		virtual std::string name() = 0;
		virtual int property1() = 0;
};

#endif
