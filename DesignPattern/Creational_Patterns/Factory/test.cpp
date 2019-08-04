#include <iostream>
#include "concrete_factory.h"

int main()
{
	Factory *f1,*f2;
	Product *p1,*p2;
	f1 = new ConcreteFactoryA;
	f2 = new ConcreteFactoryB;
	p1 = f1->produce();
	p2 = f2->produce();
	std::cout<<p1->name()<<std::endl;
	std::cout<<p2->name()<<std::endl;
	delete f1;
	delete f2;
	delete p1;
	delete p2;
}
