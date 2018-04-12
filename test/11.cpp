#include <iostream>

using namespace std;

int b = 2;
void ff(int *&a)
{
	a = &b;
}

int main()
{
	int a = 1;
	int *c = &a;
	ff(c);
	cout<<*c<<endl;
}
