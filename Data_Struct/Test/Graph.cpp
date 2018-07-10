#include "../Include/Graph.hpp"

using namespace std;

int main()
{
	// UndiGraph<char,int> aaa,bbb,ccc,ddd,eee;
	DiGraph<char,int> fff;
	// char a[] = {'A','B','A','C','B','D','E','E','F','G','E','G','G','H','A','H','H','I','C','I','C','J','D','E','E','F','A','J','B','G','D','J','C','D','D','F'};
	// int b[] = {3,2,1,0,7,4,6,3,5,4,8,2,9,7,2,4,1,4};
	// aaa.CreateGraph(a,b,sizeof(a)/sizeof(a[0]),sizeof(b)/sizeof(b[0]));
	// aaa.Dijkstra(0);
	std::cout<<std::endl;
	char a2[] = {'A','B','A','C','B','D','E','E','F','G','E','G','G','H','A','H','H','I','C','I','C','J','D','E','E','F','A','J','B','G','D','J','C','D','D','F','C','A','H','E','H','F','C','B'};
	int b2[] = {4,5,1,0,7,4,6,3,5,4,8,2,9,7,2,4,1,4,2,1,2,1};
fff.CreateGraph(a2,b2,sizeof(a2)/sizeof(a2[0]),sizeof(b2)/sizeof(b2[0]));
	fff.Dijkstra(0);
	std::cout<<std::endl;
	fff.Floyd();
   /*  aaa.DFS('A'); */
	// aaa.DFS();
	// aaa.BFS();
	// cout<<aaa.CountWeight()<<endl;
	// aaa.Prim(ddd);
	// ddd.DFS();
	// cout<<ddd.CountWeight()<<endl;
	// ccc = aaa.Kruskal();
	// ccc.DFS();
	// cout<<ccc.CountWeight()<<endl;
	// aaa.Solin(bbb);
	// bbb.DFS();
	// cout<<bbb.CountWeight()<<endl;
	// aaa.Rosenstiehl(eee);
	// eee.DFS();
	/* cout<<eee.CountWeight()<<endl; */
	return 0;
}
