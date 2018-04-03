#include<iostream>
#include<utility>
#include<string>

using namespace std;

class B 
{
	public:
		B(int i) :x(i){}
		bool operator<(const B *rhs) {cout << "operator<(const B *)" << endl;return x < rhs->x;}
		int x;
};

class A 
{
	public:
		A(int i):b(new B(i)){}
		B *b;
};

int main() 
{
	A m = 9;
	B n = 10;
	B *j = &n;
	cout<<j<<endl;
	getchar();
}
