#include "../Data_Struct/Include/sys_comm.h"

using namespace std;

struct A
{
	A* it1 = nullptr;
	A* it2 = nullptr;
};

struct B:public A
{
	int i = 0;
	B* it1 = nullptr;
	B* it2 = nullptr;
};

struct C
{
	C(){p1 = new A;}
	~C(){delete p1;}
	void ff()
	{
		A *p = new A;
		p1->it1 = p;
		cout<<"A"<<endl;
		delete p;
	}
	A* p1;
};

struct D:public C
{
	D(){q = new B;}
	~D(){delete q;}
	B* q;
};

int main()
{
	D a1;
	a1.ff();
}
