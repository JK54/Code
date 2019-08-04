#include <iostream>
#include "factory.h"

int main()
{
	Factory aaa;
	Product *p1 = aaa.produce(Factory::product_type::concreteproductA);
	Product *p2 = aaa.produce(Factory::product_type::concreteproductB);
	std::cout<<p1->name()<<std::endl;
	std::cout<<p2->name()<<std::endl;
	delete p1;
	delete p2;
}
