#include <iostream>
#include <cctype>

using namespace std;

struct ff
{
	int a = 1;
	int b = 2;
	int *c = new int[4];
	ff()
	{
		for(int i = 0;i <4;i++)
		c[i] = 5*i;
	}
	~ff(){delete [] c;}
	ff& operator=(const ff & p){a = p.a;b = p.b; c = p.c;return *this;}
	void tt()
	{
		for(int i = 0;i < 4;++i)
			cout<<c[i]<<" ";
	}
};

ff ab()
{
	ff a;
	a.a = 3;
	a.b =4;
	for(int i = 0;i < 4;i++)
		a.c[i] = 6 * i + 1;
	return a;
}

int main()
{
	ff aa;
	aa = ab();
	aa.tt();
}
