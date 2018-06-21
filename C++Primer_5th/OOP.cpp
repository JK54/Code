#include "comm.h"

using namespace std;

class second;
class first {
    friend second;

public:
    int i = 1;
    virtual void paparuazi() { cout << i << endl; }
private:
    int a = 5;
};
class second : public first {
public:
    int j = 2;
	void paparuazi() { cout << a << endl; } ;
};
class third : public second
{
	public:
		int k = 3;
		void paparuazi(){cout<<k<<endl;}
};

int main()
{
	first t;
    second i;
	third o;
    int k = 0;
    i.paparuazi();
    first* j = &o;
}
