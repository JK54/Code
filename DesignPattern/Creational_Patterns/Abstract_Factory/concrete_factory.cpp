#include "concrete_factory.h"
#include "concrete_product.h"
#include <iostream>

ConcreteFactory1::~ConcreteFactory1()
{
	std::cout<<"destroy factory1.."<<std::endl;
}

ProductA* ConcreteFactory1::createproductA()
{
	ProductA *p = new ConcreteProductA1;
	return p;
}

ProductB* ConcreteFactory1::createproductB()
{
	ProductB *p = new ConcreteProductB1;
	return p;
}

ConcreteFactory2::~ConcreteFactory2()
{
	std::cout<<"destroy factory2.."<<std::endl;
}

ProductA* ConcreteFactory2::createproductA()
{
	ProductA *p = new ConcreteProductA2;
	return p;
}

ProductB* ConcreteFactory2::createproductB()
{
	ProductB *p = new ConcreteProductB2;
	return p;
}
