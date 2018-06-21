#include <iostream>
#include <string>
using namespace std;
int main()
{
	string line1,line2;
	cout<<"input line1"<<endl;
	getline(cin,line1);
	cout<<"input line2"<<endl;
	getline(cin,line2);
	if(line1.size() >= line2.size())
		cout<<line1<<endl;
	else
		cout<<line2<<endl;

}
