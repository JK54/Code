#include "concrete_product.h"
#include <iostream>
#include <string>

ConcreteProductA1::ConcreteProductA1()
{
	p1 = 1;
}

ConcreteProductA1::ConcreteProductA1(const int &t1)
{
	p1 = t1;
}

ConcreteProductA1::~ConcreteProductA1()
{
	std::cout<<"destroy productA1"<<std::endl;
}

std::string ConcreteProductA1::name()
{
	std::string res("This is productA1");
	return res;
}

int ConcreteProductA1::property1()
{
	return p1;
}

ConcreteProductA2::ConcreteProductA2()
{
	p1 = 2;
}

ConcreteProductA2::ConcreteProductA2(const int &t1)
{
	p1 = t1;
}

ConcreteProductA2::~ConcreteProductA2()
{
	std::cout<<"destroy productA2"<<std::endl;
}

std::string ConcreteProductA2::name()
{
	std::string res("This is productA2");
	return res;
}

int ConcreteProductA2::property1()
{
	return p1;
}

ConcreteProductB1::ConcreteProductB1()
{
	p1 = 1;
}

ConcreteProductB1::ConcreteProductB1(const int &t1)
{
	p1 = t1;
}

ConcreteProductB1::~ConcreteProductB1()
{
	std::cout<<"destroy productB1"<<std::endl;
}

std::string ConcreteProductB1::name()
{
	std::string res("This is productB1");
	return res;
}

int ConcreteProductB1::property1()
{
	return p1;
}

ConcreteProductB2::ConcreteProductB2()
{
	p1 = 2;
}

ConcreteProductB2::ConcreteProductB2(const int &t1)
{
	p1 = t1;
}

ConcreteProductB2::~ConcreteProductB2()
{
	std::cout<<"destroy productB2"<<std::endl;
}

std::string ConcreteProductB2::name()
{
	std::string res("This is productB2");
	return res;
}

int ConcreteProductB2::property1()
{
	return p1;
}
