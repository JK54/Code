#include "../Include/Graph.hpp"

using namespace std;

int main()
{
	UndiGraph<char,int> aaa,bbb,ccc;
	char a[] = {'A','B','B','E','B','D','D','E','C','B','A','C','C','D','A','E','C','E'};
	int b[] = {4,3,2,1,5,6,7,3,4};
	aaa.CreateGraph(a,b,sizeof(a)/sizeof(a[0]),sizeof(b)/sizeof(b[0]));
	aaa.DFS();
	aaa.Solin(bbb);
	ccc = aaa.Kruskal();
	cout<<bbb.CountWeight()<<endl;
	bbb.DFS();
	cout<<ccc.CountWeight()<<endl;
	ccc.DFS();
}
