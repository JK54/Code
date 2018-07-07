#include <iostream>
#include <string>
#include <vector>
using namespace std;


size_t count_calls(int j)
{
		static size_t ctr = 0;
		int i = 0;
		j = 5;
		return ctr++ + i++;
}
int main()
{
		int i;
		for(size_t i = 0 ; i != 10; ++i)
				cout<<count_calls(i)<<endl;
		return 0;
}

