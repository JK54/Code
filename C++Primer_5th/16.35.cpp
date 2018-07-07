#include "comm.h"

using namespace std;

template<typename T> 
T calc(T v1,int v2)
{
	cout<<"calc.."<<endl;
	cout<<v1+static_cast<T>(v2)<<endl;
	return v1+static_cast<T>(v2);
}
template<typename T> 
T fcn(T v1,T v2)
{
	cout<<"fcn..."<<endl;
	cout<<v1 + v2<<endl;
	return v1 + v2;
}

int main()
{
	double d = 1.0;
	float f = 2.0;
	char c = 'c';
	calc(c,'c');
	calc(d,f);
	fcn(c,'c');
	fcn(d,f);
}
