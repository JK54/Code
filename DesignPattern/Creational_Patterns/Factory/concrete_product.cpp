#include "concrete_product.h"
#include <iostream>

std::string ConcreteProductA::name()
{
	std::string str("This is ProductA");
	return str;
}

std::string ConcreteProductB::name()
{
	std::string str("This is ProductB");
	return str;
}
