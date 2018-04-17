#include <iostream>
#include <string>
#include <vector>
using namespace std;

void reset(int &i)
{
		i = 0;
		cout<<&i<<"\t"<<i<<endl;
}
void reset1(int *i)
{
		*i = 0;
		cout<<i<<"\t"<<*i<<endl;
}
int main()
{
		int j = 50;
//		int *i = &j;
//		reset(*i);
//		cout<<i<<"\t"<<*i<<endl;
		int &i = j;
		reset(j);
		cout<<&j<<"\t"<<j<<endl;
		return 0;
}

