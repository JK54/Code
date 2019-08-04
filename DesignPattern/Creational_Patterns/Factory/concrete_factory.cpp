#include "concrete_factory.h"
#include "concrete_product.h"

Product* ConcreteFactoryA::produce()
{
	Product *p = new ConcreteProductA;
	return p;
}

Product* ConcreteFactoryB::produce()
{
	Product *p = new ConcreteProductB;
	return p;
}
