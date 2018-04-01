#include <iostream>
#include <string>
using namespace std;
int main()
{
	string line,tmp;
	while(getline(cin,tmp))
		line += tmp;
	cout<<line<<endl;
}
