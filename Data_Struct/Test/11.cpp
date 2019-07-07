#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int>aaa;
	for(int i = 0;i < 10;i++)
		aaa.push_back(i);
	for(int i = 0;i<10;i++,aaa.pop_back())
		cout<<aaa.back()<<std::endl;
}
