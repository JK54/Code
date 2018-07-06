#include "16.4.h"

using namespace std;

int main()
{
	vector<int> vi{1,2,3,4,5,6,7,8,9,0};
	list<string> sl{"a","b","c","d","e"};
	findl(vi.begin(),vi.end(),4);
	findl(sl.begin(),sl.end(),"d");
}
