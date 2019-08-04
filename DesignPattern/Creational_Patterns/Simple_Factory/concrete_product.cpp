#include "concrete_product.h"

using std::string;

string ConcreteProductA::name()
{
	string str("This is ConcreteProductA");
	return str;
}

string ConcreteProductB::name()
{
	string str("This is ConcreteProductB");
	return str;
}
