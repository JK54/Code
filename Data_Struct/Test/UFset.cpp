#include "../Include/UFSet.hpp"

int main()
{
	UFSet<int> aaa(10);
	aaa.Merge(0,1);
	aaa.Merge(2,3);
	aaa.Merge(4,5);
	aaa.Merge(2,4);
	aaa.Merge(0,2);
	aaa.CollapsePath(5);
}
