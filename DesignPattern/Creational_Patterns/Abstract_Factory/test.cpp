#include "concrete_factory.h"
#include <iostream>

int main()
{
	ConcreteFactory1 AAA;
	ConcreteFactory2 BBB;
	ProductA *aa = AAA.createproductA();
	ProductB *ab = AAA.createproductB();
	ProductA *ba = BBB.createproductA();
	ProductB *bb = BBB.createproductB();
	std::cout<<aa->name()<<std::endl;
	std::cout<<ab->name()<<std::endl;
	std::cout<<ba->name()<<std::endl;
	std::cout<<bb->name()<<std::endl;
	std::cout<<aa->property1()<<std::endl;
	std::cout<<ab->property1()<<std::endl;
	std::cout<<ba->property1()<<std::endl;
	std::cout<<bb->property1()<<std::endl;
	delete aa;
	delete ab;
	delete ba;
	delete bb;
}
