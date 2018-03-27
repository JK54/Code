#include "comm.h"

using namespace std;

int main()
{
	int a = 1;
	int b = 4;
	auto f = [a,b]{return a + b;};
	cout<<f()<<endl;
}
