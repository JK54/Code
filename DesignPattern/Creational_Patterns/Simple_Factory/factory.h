#ifndef _SFACTORY_H
#define _SFACTORY_H

#include "concrete_product.h"

class Factory
{
	public:
		enum product_type{concreteproductA,concreteproductB};
	public:
		Product* produce(product_type);
};

#endif
