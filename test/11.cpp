#include <iostream>

using namespace std;

void ff(char *a[])
{
	cout<<"didi"<<endl;
}

int main()
{
	char *a[3];
	for(int i = 0;i<3;++i)
	{
		a[i] = new char[i];
		ff(&a[i]);
	}
}
