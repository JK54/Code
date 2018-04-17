#include "comm.h"

using namespace std;

int main()
{
		vector<int> a;
		vector<int> b(a);
		vector<int> c{1,2,3,4};
		vector<double> f(10,42);
		vector<int> e(10);
		vector<int> d(f.begin(),f.end());
		for(auto i:d)
				cout<<i<<endl;

}
