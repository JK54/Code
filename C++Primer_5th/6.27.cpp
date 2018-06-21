#include "comm.h"
#include<initializer_list>
using namespace std;


int add_all(std::initializer_list<int>la)
{
		int result = 0;
		for(auto i:la)
				result += i;
		cout<<result<<endl;
		return result;
}

int main()
{
		initializer_list<int> a = {1,2,3,4999,56,7,8,9,10};
		add_all(a);
		return 0;
}
