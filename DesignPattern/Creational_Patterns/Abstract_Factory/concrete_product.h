#ifndef _CONCRETE_PRODUCT_H
#define _CONCRETE_PRODUCT_H

#include "product.h"
#include <string>

class ConcreteProductA1 :public ProductA
{
	public:
		ConcreteProductA1();
		explicit ConcreteProductA1(const int &);
		virtual ~ConcreteProductA1();
		virtual std::string name();
		virtual int property1();
	private:
		int p1;
};

class ConcreteProductA2 : public ProductA
{
	public:
		ConcreteProductA2();
		explicit ConcreteProductA2(const int &);
		virtual ~ConcreteProductA2();
		virtual std::string name();
		virtual int property1();
	private:
		int p1;
};

class ConcreteProductB1 : public ProductB
{
	public:
		ConcreteProductB1();
		explicit ConcreteProductB1(const int &);
		virtual ~ConcreteProductB1();
		virtual std::string name();
		virtual int property1();
	private:
		int p1;
};

class ConcreteProductB2 : public ProductB
{
	public:
		ConcreteProductB2();
		explicit ConcreteProductB2(const int &);
		virtual ~ConcreteProductB2();
		virtual std::string name();
		virtual int property1();
	private:
		int p1;
};

#endif
