#include "comm.h"

using namespace std;

int main()
{
	int a = 4;
	auto  f =[a](int b)-> int{return a + b;};
	cout<<f(5)<<endl;
}
