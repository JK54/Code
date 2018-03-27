#include "comm.h"
#include <list>

using namespace std;

int main()
{
		list<int> list1{1,2,3,4,5,6,7,8,9,10};
		vector<double> vec1(list1.begin(),list1.end());
		vector<int> vec2{1,2,3,4,5,6,7,8,9,10,11};
		vector<int>vec3;
		vec3.assign(vec2.begin(),vec2.begin()+3);
		vector<int>::iterator ite1 = vec2.end() - 1;
		swap(vec2,vec3);
		for(auto i :vec2)
				cout<<i<<" ";
		cout<<endl;
		cout<<*ite1<<endl;
		for(auto i :vec3)
				cout<<i<<" ";
		cout<<endl;
}
