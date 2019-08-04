#include "factory.h"

Product* Factory::produce(product_type type)
{
	Product *product = nullptr;
	switch(type)
	{
		case product_type::concreteproductA:
			product = new ConcreteProductA;
			break;
		case product_type::concreteproductB:
			product = new ConcreteProductB;
			break;
	}
	return product;
}
