#ifndef _FFACTORY_H
#define _FFACTORY_H

#include "product.h"

class Factory
{
	public:
		virtual ~Factory(){}
		virtual Product* produce() = 0;
};

#endif
