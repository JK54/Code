#include "../GenList.h"
using namespace std;
int main()
{
	ifstream in("genlist.txt");
	GenList<int> aaa;
	Createlist(aaa.First(),in);
	Traverse(aaa.First());
	cout<<endl;
	cout<<aaa.Depth()<<endl;
	cout<<aaa.Length()<<endl;
}
