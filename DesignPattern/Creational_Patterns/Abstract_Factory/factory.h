#ifndef _FACTORY_H
#define _FACTORY_H

#include "product.h"

class Factory
{
	public:
		virtual ~Factory(){}
		virtual ProductA* createproductA() = 0;
		virtual ProductB* createproductB() = 0;
};

#endif
