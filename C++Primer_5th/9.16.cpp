#include "comm.h"
#include<array>
#include <list>
#include <fstream>
using std::vector;
using std::cout;
using std::endl;
using std::list;
int main()
{
		list<int> a{1,2,3};
		vector<int> b{1,9};
		bool c = vector<int>(a.begin(),a.end())<b;
		cout<<c <<endl;

}
