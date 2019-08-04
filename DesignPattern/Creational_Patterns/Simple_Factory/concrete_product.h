#ifndef _CONCRETE_SPRODUCT_H
#define _CONCRETE_SPRODUCT_H

#include "product.h"

class ConcreteProductA : public Product
{
		public:
			virtual std::string name() override;
};

class ConcreteProductB : public Product
{
		public:
			virtual std::string name() override;
};
#endif
