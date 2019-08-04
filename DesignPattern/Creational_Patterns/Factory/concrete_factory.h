#ifndef _FCONCRETE_FACTORY_H
#define _FCONCRETE_FACTORY_H

#include "factory.h"
#include "concrete_product.h"

class ConcreteFactoryA : public Factory
{
	public:
		~ConcreteFactoryA() = default;
		virtual Product* produce();
};

class ConcreteFactoryB : public Factory
{
	public:
		~ConcreteFactoryB() = default;
		virtual Product* produce();
};

#endif
