#include "../Include/Graph.hpp"

using namespace std;

int main()
{
	UndiGraph<char,int> aaa,bbb,ccc,ddd,eee;
	char a[] = {'A','B','A','C','B','D','E','E','F','G','E','G','G','H','A','H','H','I','C','I','C','J','D','E','E','F','A','J','B','G','D','J','C','D','D','F'};
	int b[] = {3,2,1,0,7,4,6,3,5,4,8,2,9,7,2,4,1,4};
	aaa.CreateGraph(a,b,sizeof(a)/sizeof(a[0]),sizeof(b)/sizeof(b[0]));
	aaa.DFS('A');
	aaa.DFS();
	aaa.BFS();
	cout<<aaa.CountWeight()<<endl;
	aaa.Prim(ddd);
	ddd.DFS();
	cout<<ddd.CountWeight()<<endl;
	ccc = aaa.Kruskal();
	ccc.DFS();
	cout<<ccc.CountWeight()<<endl;
	aaa.Solin(bbb);
	bbb.DFS();
	cout<<bbb.CountWeight()<<endl;
	aaa.Rosenstiehl(eee);
	eee.DFS();
	cout<<eee.CountWeight()<<endl;
return 0;
}
