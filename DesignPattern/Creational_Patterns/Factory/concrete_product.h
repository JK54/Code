#ifndef _FCONCRETE_PRODUCT_H
#define _FCONCRETE_PRODUCT_H

#include "product.h"

class ConcreteProductA : public Product
{
	public:
		virtual std::string name();
};

class ConcreteProductB : public Product
{
	public:
		virtual std::string name();
};
#endif
