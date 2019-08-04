#ifndef _CONCRETE_FACTORY_H
#define _CONCRETE_FACTORY_H

#include "product.h"
#include "factory.h"

class ConcreteFactory1 : public Factory
{
	public:
		virtual ~ConcreteFactory1();
		virtual ProductA* createproductA();
		virtual ProductB* createproductB();
};

class ConcreteFactory2 : public Factory
{
	public:
		virtual ~ConcreteFactory2();
		virtual ProductA* createproductA();
		virtual ProductB* createproductB();
};

#endif
