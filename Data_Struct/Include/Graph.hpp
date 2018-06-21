#ifndef _GRAPH_H
#define _GRAPH_H

#include "sys_comm.h"
#include "Queue.hpp"
#include "Stack.hpp"
#include "UFSet.hpp"
#include "Heap_Array.hpp"
#define MAXVERT 100
#define MAXWEIGHT 32767

//ps:In the Edge and WEdge object,the definition of dest is the same as the source vertex,which means they are the index of array.Remember when calling them outside,they are begin from 1.and will minus one when dealing with the vertex.
//the definition of traverse is to visit all the vertex ,while not the edge.
//abstract base class of weighted graph
template<typename T,typename K>
class WEdge
{
	public:
		WEdge(const int &d,const K &c):dest(d - 1),cost(c),next(nullptr){}
		int dest;
		K cost;
		WEdge<T,K> *next;
};
template<typename T,typename K>
class WVertex
{
	public:
		WVertex(const T &d):data(d),adj(nullptr){}
		WVertex():adj(nullptr){}
		T data;
		WEdge<T,K> *adj;
};
template<typename T, typename K>
class WGraph
{
	public:
		WGraph(int max = MAXVERT,int mw = MAXWEIGHT):maxvertex(max),currentvertex(0),currentedge(0),maxweight(mw){}
		~WGraph() = default;
		bool IsEmpty(){return currentedge == 0;}
		int NumOfVertex(){return currentvertex;}
		int NumOfEdge(){return currentedge;}
		//the definition of full graph between Undigraph and Digraph is that Direct is double sizes of Undi
		virtual void CreateGraph(const T *,const K *,const int &,const int &) = 0;
		virtual void CreateGraph(std::istream &is) = 0;
		virtual bool IsFull() = 0;
		virtual T GetValue(const int &i) = 0;
		virtual int GetVertexPos(const T &v) = 0;
		virtual K GetWeight(const int &v1,const int &v2) const = 0;
		virtual int GetFirstNeighbor(const int &v) = 0;
		virtual int GetNextNeighbor(const int &v,const int &w) = 0;
		virtual bool InsertVertex(const T &ver) = 0;
		virtual bool InsertEdge(const int &v1,const int &v2,const K &weight) = 0;
		virtual bool RemoveVertex(const int &i) = 0;
		virtual bool RemoveEdge(const int &v1,const int &v2) = 0;
		virtual void DFS() = 0;
		virtual void DFS(const T &) = 0;
		virtual void BFS() = 0;
		virtual void BFS(const T &) = 0;
	protected:
		int maxvertex;
		int currentvertex;
		int currentedge;
		K maxweight;
		bool isvalid(const int &v1,const int &v2) const;
};

//abstract base class of non-weighted graph
template<typename T>
struct Edge
{
	Edge(const int &d):dest(d - 1),next(nullptr){}
	int dest;
	Edge<T> *next;
};
template<typename T>
struct Vertex
{
	Vertex(const T &d):data(d),adj(nullptr){}
	T data;
	Edge<T> *adj;
};

template<typename T>
class Graph
{
	public:
		Graph(int max = MAXVERT):maxvertex(max),currentvertex(0),currentedge(0){}
		~Graph() = default;

		bool IsEmpty(){return currentedge == 0;}
		int NumOfVertex(){return currentvertex;}
		int NumOfEdge(){return currentedge;}
		//the definition of full graph between Undigraph and Digraph is that Digraph is double sizes of Undi.
		virtual void CreateGraph(const T *,const int &n) = 0;
		virtual void CreateGraph(std::istream &is) = 0;
		virtual bool IsFull() = 0;
		virtual T GetValue(const int &i) = 0;
		virtual int GetVertexPos(const T &v) = 0;
		virtual int GetFirstNeighbor(const int &v) = 0;
		virtual int GetNextNeighbor(const int &v,const int &w) = 0;
		virtual bool InsertVertex(const T &ver) = 0;
		virtual bool InsertEdge(const int &v1,const int &v2) = 0;
		virtual bool RemoveVertex(const int &i) = 0;
		virtual bool RemoveEdge(const int &v1,const int &v2) = 0;
	protected:
		int maxvertex;
		int currentvertex;
		int currentedge;
		bool isvalid(const int &v1,const int &v2) const;
};

//--------------------declaration of weighted undigraph-----------------
template<typename K>
class MinEdge;

template<typename T,typename K>
class UndiGraph:public WGraph<T,K>
{
	public:
		UndiGraph():WGraph<T,K>(){NodeTable = new WVertex<T,K>[this->maxvertex];}
		UndiGraph(int x):WGraph<T,K>(x){NodeTable = new WVertex<T,K>[this->maxvertex];}
		UndiGraph(const UndiGraph<T,K> &p);
		~UndiGraph();
		UndiGraph<T,K>& operator=(const UndiGraph<T,K> &p);
		UndiGraph<T,K>& operator=(UndiGraph<T,K> &&p);
		virtual void CreateGraph(const T *,const K *,const int &,const int &) override;
		virtual void CreateGraph(std::istream &is) override;
		virtual bool IsFull() override;
		virtual T GetValue(const int &i) override;
		virtual K GetWeight(const int &v1,const int &v2) const override;
		virtual int GetVertexPos(const T &v) override;
		virtual int GetFirstNeighbor(const int &v) override;
		virtual int GetNextNeighbor(const int &v,const int &w) override;
		virtual bool InsertVertex(const T &ver) override;
		virtual bool InsertEdge(const int &v1,const int &v2,const K &weight) override;
		virtual bool RemoveVertex(const int &i) override;
		virtual bool RemoveEdge(const int &v1,const int &v2) override;
		//----------------traverse-----------------
		//parameter means assiginng the begin vertex or not
		virtual void DFS(const T &) override;
		virtual	void DFS() override;
		virtual	void BFS(const T &) override;
		virtual void BFS() override;
		//----------------application of traverse------------
		bool IsTree();
		bool IsInLoop(const int &v1,const int &v2);
		K CountWeight();
		//here abandon the weight value,if necessary,modify the tree node type to receive the weight.
		void CreateForest(Forest<T> &result);
		//----------------Minimum-Cost Spanning Tree------
		UndiGraph<T,K> Kruskal();
		void Prim(UndiGraph<T,K> &);
		void Solin(UndiGraph<T,K> &);
		void Rosenstiehl(UndiGraph<T,K> &);
		void Dijkstra();

	private:
		WVertex<T,K> *NodeTable;

		bool removeedge(const int &v1,const int &v2);
		void dfs(const int &,bool *);
		void udfs(const int &);
		void bfs(const T &);
		int minedge(int source,bool *);
};

//--------------------declaration of weighted digraph------------
template<typename T,typename K>
class DiGraph:public WGraph<T,K>
{
	public:	
		DiGraph():WGraph<T,K>(){InNodeTable = new WVertex<T,K>[this->maxvertex],OutNodeTable = new WVertex<T,K>[this->maxvertex];}
		DiGraph(int x):WGraph<T,K>(x){InNodeTable = new WVertex<T,K>[this->maxvertex],OutNodeTable = new WVertex<T,K>[this->maxvertex];}
		~DiGraph();
		virtual void CreateGraph(const T *,const K *,const int &n) override;
		virtual void CreateGraph(std::istream &is) override;
		virtual bool IsFull() override;
		virtual T GetValue(const int &i) override;
		virtual K GetWeight(const int &v1,const int &v2) override;
		virtual int GetVertexPos(const T &v) override;
		virtual int GetFirstNeighbor(const int &v) override;
		virtual int GetNextNeighbor(const int &v,const int &w) override;
		virtual bool InsertVertex(const T &ver) override;
		virtual bool InsertEdge(const int &v1,const int &v2,const K &weight) override;
		virtual bool RemoveVertex(const int &i) override;
		virtual bool RemoveEdge(const int &v1,const int &v2) override;
	private:
		WVertex<T,K> *InNodeTable;
		WVertex<T,K> *OutNodeTable;
};
//---------------------common function-------------------------------------
template<typename T,typename K>
bool WGraph<T,K>::isvalid(const int &v1,const int &v2) const 
{
	if((v1 < 1 || v1 > this->currentvertex) || (v2 < 1 || v2 > this->currentvertex) || v1 == v2)
	{
	   /*  if(v1 == v2 && (v1 >= 1 || v1 <= this->currentvertex)) */
			// std::cout<<"one vertex does not have loop edge!"<<std::endl;
		// else
			/* std::cout<<"invalid vertex"	<<std::endl; */
		return false;
	}
	return true;
}
	
template<typename T>
bool Graph<T>::isvalid(const int &v1,const int &v2) const 
{
	if((v1 < 1 && v1 > this->currentvertex) || (v2 < 1 && v2 > this->currentvertex) || v1 == v2)
	{
	   /*  if(v1 == v2 && (v1 >= 1 || v1 <= this->currentvertex)) */
			// std::cout<<"one vertex does not have loop edge!"<<std::endl;
		// else
			/* std::cout<<"invalid vertex"	<<std::endl; */
		return false;
	}
	return true;
}

//----------------------definition of weighted-undigraph---------------
template<typename T,typename K>
UndiGraph<T,K>::~UndiGraph()
{
	while(this->currentvertex > 0)
		RemoveVertex(this->currentvertex);
	delete [] NodeTable;
}
template<typename T,typename K>		
UndiGraph<T,K>::UndiGraph(const UndiGraph<T,K> &p)
{
	this->operator=(p);
}

template<typename T,typename K>		
UndiGraph<T,K>& UndiGraph<T,K>::operator=(const UndiGraph<T,K> &p)
{
	this->~UndiGraph();
	NodeTable = new WVertex<T,K>[p.maxvertex];
	for(int i = 0;i < p.currentvertex;i++)
		InsertVertex(p.NodeTable[i].data);
	for(int i = 1;i <= p.currentvertex;i++)
		for(int j = i + 1;j <= p.currentvertex;j++)
			if(p.GetWeight(i,j) != p.maxweight)
				InsertEdge(i,j,p.GetWeight(i,j));
	return *this;
}

template<typename T,typename K>		
UndiGraph<T,K>& UndiGraph<T,K>::operator=(UndiGraph<T,K> &&p)
{
	this->~UndiGraph();
	// UndiGraph<T,K> q = std::move(p);
	NodeTable = new WVertex<T,K>[p.maxvertex];
	for(int i = 0;i < p.currentvertex;i++)
		InsertVertex(p.NodeTable[i].data);
	for(int i = 1;i <= p.currentvertex;i++)
		for(int j = i + 1;j <= p.currentvertex;j++)
			if(p.GetWeight(i,j) != p.maxweight)
				InsertEdge(i,j,p.GetWeight(i,j));
	return *this;
}
template<typename T,typename K>
void UndiGraph<T,K>::CreateGraph(const T *d,const K *w,const int &nd,const int &nw)
{
	for(int i = 0;i < nd;i++)
		InsertVertex(d[i]);
	for(int i = 0;i < nw;i++)
	{
		InsertEdge(GetVertexPos(d[2 * i]),GetVertexPos(d[2 * i + 1]),w[i]);
	}
}

template<typename T,typename K>
void UndiGraph<T,K>::CreateGraph(std::istream &is)
{
	T v1,v2;
	K we;
	while(is>>v1>>v2>>we)
	{
		InsertVertex(v1);
		InsertVertex(v2);
		InsertEdge(GetVertexPos(v1),GetVertexPos(v2),we);
	}
}

template<typename T,typename K>
bool UndiGraph<T,K>::IsFull()
{
	int e = this->currentedge;
	int v = this->currentvertex;
	return v == this->maxvertex && e == v*(v - 1)/2;
}

template<typename T,typename K>
T UndiGraph<T,K>::GetValue(const int &i)
{
	return NodeTable[i - 1].data;
}

template<typename T,typename K>
K UndiGraph<T,K>::GetWeight(const int &v1,const int &v2) const 
{
	if(!this->isvalid(v1,v2))
		return this->maxweight;
	WEdge<T,K> *trav = NodeTable[v1 - 1].adj;
	while(trav != nullptr && trav->dest != v2 - 1)
		trav = trav->next;
	if(trav == nullptr)
		return this->maxweight;
	else
		return trav->cost;
}
template<typename T,typename K>
int UndiGraph<T,K>::GetVertexPos(const T &v)
{
	int i;
	for(i = 0;NodeTable[i].data != v && i < this->currentvertex;i++);
	if(NodeTable[i].data != v)
		return -1;
	else
		return i + 1;
}

template<typename T,typename K>
int UndiGraph<T,K>::GetFirstNeighbor(const int &v)
{
	if(v < 1 && v > this->currentvertex)
	{
		std::cout<<"invalid vertex"<<std::endl;
		exit(1);
	}
	WEdge<T,K> *e = NodeTable[v - 1].adj;
	if(e != nullptr)
		return e->dest + 1;
	else
		return -1;
}

template<typename T,typename K>
int UndiGraph<T,K>::GetNextNeighbor(const int &v,const int &w)
{
	if(!this->isvalid(v,w))
		return -1;
	WEdge<T,K> *trav = NodeTable[v - 1].adj;
	while(trav != nullptr && trav->dest != w -1)
		trav = trav->next;
	if(trav->dest != w - 1)
	{
		std::cout<<"the two vertex are not connected"<<std::endl;
		return -1;
	}
	if(trav->next != nullptr)
		return trav->next->dest + 1;
	else
		return -1;
}
template<typename T,typename K>
bool UndiGraph<T,K>::InsertVertex(const T &ver)
{
	if(this->currentvertex == this->maxvertex)
	{
		std::cout<<"the vertex array is full"<<std::endl;
		return false;
	}
	if(GetVertexPos(ver) == -1)
		NodeTable[this->currentvertex++].data = ver;
	else
		return false;
	return true;
}
template<typename T,typename K>
bool UndiGraph<T,K>::InsertEdge(const int &v1,const int &v2,const K &weight)
{
	if(!this->isvalid(v1,v2))
		return false;
	WEdge<T,K> *tmpv1 = new WEdge<T,K>(v2,weight);
	WEdge<T,K> *tmpv2 = new WEdge<T,K>(v1,weight);
	WEdge<T,K> *trav = NodeTable[v1 - 1].adj;
	while(trav != nullptr)
	{
		if(trav->dest == v2 - 1)
		{
			std::cout<<"the edge is already existed.."<<std::endl;
			return false;
		}
		trav = trav->next;
	}
	tmpv1->next = NodeTable[v1 - 1].adj;
	NodeTable[v1 - 1].adj = tmpv1;
	tmpv2->next = NodeTable[v2 - 1].adj;
	NodeTable[v2 - 1].adj = tmpv2;
	this->currentedge++;
	return true;
}

template<typename T,typename K>
bool UndiGraph<T,K>::removeedge(const int &v1,const int &v2)
{
	WEdge<T,K> *trav = NodeTable[v1 - 1].adj;
	WEdge<T,K> *pre = trav;
	while(trav->dest != v2 - 1 && trav != nullptr)
	{
		pre = trav;
		trav = trav->next;
	}
	if(trav == nullptr)
	{
		std::cout<<"the edge is not existed"<<std::endl;
		return false;
	}
	//edge is the first neighbor
	if(pre == trav)
		NodeTable[v1 - 1].adj = trav->next;
	else
		pre->next = trav->next;
	delete trav;
	trav = nullptr;
	return true;
}
template<typename T,typename K>
bool UndiGraph<T,K>::RemoveEdge(const int &v1,const int &v2)
{
	if(!this->isvalid(v1,v2))
		return false;
	if(!removeedge(v1,v2))
		return false;
	removeedge(v2,v1);
	this->currentedge--;
	return true;
}

template <typename T,typename K>
bool UndiGraph<T,K>::RemoveVertex(const int &v1)
{
	if(v1 < 1 || v1 > this->currentvertex)
	{
		std::cout<<"the vertex is invalid"<<std::endl;
		return false;
	}
	while(NodeTable[v1 - 1].adj != nullptr)
		RemoveEdge(v1,NodeTable[v1 - 1].adj->dest + 1);
	for(int i = v1;i < this->currentvertex;i++)
		NodeTable[i - 1] = NodeTable[i];
	this->currentvertex--;
	return true;
}

template<typename T,typename K>
void UndiGraph<T,K>::BFS(const T &v)
{
	bfs(v);
}
template<typename T,typename K>
void UndiGraph<T,K>::BFS()
{
	bfs(NodeTable[0].data);
}
template<typename T,typename K>
void UndiGraph<T,K>::bfs(const T &v)
{
	bool *visited = new bool[this->currentvertex];
	int trav,loc = GetVertexPos(v);
	Queue<int> q;
	for(int i = 0;i<this->currentvertex;i++)
		visited[i] = false;
	std::cout<<NodeTable[loc - 1].data<<" ";
	visited[loc - 1] = true;
	q.Enqueue(loc);
	while(!q.IsEmpty())
	{
		q.Dequeue(loc);
		trav = GetFirstNeighbor(loc);
		while(trav != -1)
		{
			if(visited[trav - 1] == false)
			{
				visited[trav - 1] = true;
				std::cout<<NodeTable[trav - 1].data<<" ";
				q.Enqueue(trav);
			}
			trav = GetNextNeighbor(loc,trav);
		}
	}
	std::cout<<std::endl;
	delete [] visited;
}

template<typename T,typename K>
void UndiGraph<T,K>::DFS(const T &v)
{
	bool *visited = new bool[this->currentvertex];
	for(int i = 0;i<this->currentvertex;i++)
		visited[i] = false;
	dfs(GetVertexPos(v),visited);
	std::cout<<std::endl;
	delete [] visited;
}
template<typename T,typename K>
void UndiGraph<T,K>::DFS()
{
	bool *visited = new bool[this->currentvertex];
	for(int i = 0;i<this->currentvertex;i++)
		visited[i] = false;
	udfs(1);
	std::cout<<std::endl;
	delete [] visited;
}

template<typename T,typename K>
void UndiGraph<T,K>::dfs(const int &v,bool visited[])
{
	std::cout<<NodeTable[v - 1].data<<" ";
	visited[v - 1] = true;
	int w = GetFirstNeighbor(v);
	while(w != -1)
	{
		if(visited[w - 1] == false)
			dfs(w,visited);
		w = GetNextNeighbor(v,w);
	}
}

template<typename T,typename K>
void UndiGraph<T,K>::udfs(const int &v)
{
	bool *visited = new bool[this->currentvertex];
	Stack<int> s;
	int tp,trav = v;
	for(int i = 0;i < this->currentvertex;i++)
		visited[i] = false;
	s.Push(trav);
	visited[trav - 1] = true;
	while(!s.IsEmpty())
	{
		s.Pop(trav);
		std::cout<<NodeTable[trav - 1].data<<" ";
		tp = GetFirstNeighbor(trav);
		while(tp != -1)
		{
			if(visited[tp - 1] == false)
			{
				s.Push(tp);
				visited[tp - 1] = true;
			}
			tp = GetNextNeighbor(trav,tp);
		}
	}
}

template<typename T,typename K>
bool UndiGraph<T,K>::IsTree()
{
	if(this->currentedge + 1 != this->currentvertex)
		return false;
	bool *visited = new bool[this->currentvertex];
	for(int i = 0;i < this->currentvertex;i++)
		visited[i] = false;
	dfs(1,visited);
	for(int i = 0;i<this->currentvertex;i++)
		if(visited[i] == false)
		{
			delete [] visited;
			return false;
		}
	delete [] visited;
	return true;
}

template<typename T,typename K>
bool UndiGraph<T,K>::IsInLoop(const int &v1,const int &v2)
{
	UFSet<int> u(this->currentvertex);
	int tp = GetFirstNeighbor(v1);
	int i = 0,j = 0;
	while(tp != -1)
	{
		i++;
		u.Union(v1 - 1,tp - 1);
		tp = GetNextNeighbor(v1,tp);
	}
	//the auxiliary array record the child of v1.
	int *v1child = new int[i];
	for(i = 0,j = 0;j < this->currentvertex;j++)
		if(u.Find(j) == v1 - 1)
			v1child[i++] = j;

}
template<typename T,typename K>
K UndiGraph<T,K>::CountWeight()
{
	K result = 0;
	for(int i = 1;i <= this->currentvertex;i++)	
		for(int j = i + 1;j <= this->currentvertex;j++)
			if(GetWeight(i,j) != this->maxweight)
				result += GetWeight(i,j);
	return result;
}
template<typename T,typename K>
void UndiGraph<T,K>::CreateForest(Forest<T> &result)
{}

//----------------MST----------------------------------
template <typename K>
class MinEdge
{
	public:
		MinEdge():i(0),j(0){}
		MinEdge(int x,int y,K w):i(x),j(y),weight(w){}
		MinEdge<K>& operator=(const MinEdge<K> &p){i = p.i;j=p.j;weight=p.weight;return *this;}
		bool operator<=(const MinEdge<K> &p){return weight <= p.weight;}
		bool operator>(const MinEdge<K> &p){return weight > p.weight;}
		int i,j;
		K weight;
};

//Main idea of Kruskal: 
//it is suitable from the sparse graph.
//1.bulid a vertex set contains all the vertex;
//2.order edges in weight ascending order;
//3.select edge from the edge set,if the head and tail vertex is already connected,then abondan the edge,continuing the process until the edge num of result is vertex minus 1.
template<typename T,typename K>
UndiGraph<T,K> UndiGraph<T,K>::Kruskal()
{
	int i,j;
	bool *connected = new bool[this->currentvertex];
	MinHeap<MinEdge<K>> h;
	MinEdge<K> trav;
	UndiGraph<T,K> result;
	//construct a graph with all vertexs and zero edge.
	for(i = 0;i < this->currentvertex;i++)
		result.InsertVertex(NodeTable[i].data);
	//init the connected array.
	for(i = 0;i < this->currentvertex;i++)
		connected[i] = false;
	//build the minheap of edges.
	for(i = 1;i <= this->currentvertex;i++)
	{
		for(j = i + 1; j <= this->currentvertex;j++)
			if(GetWeight(i,j) != this->maxweight)
				h.Insert(MinEdge<K>(i,j,GetWeight(i,j)));
	}
	//the main process
	while(result.currentedge != result.currentvertex - 1)
	{
		h.Remove(trav);
		if(connected[trav.i - 1] == false || connected[trav.j - 1] == false)
		{
			result.InsertEdge(trav.i,trav.j,trav.weight);
			connected[trav.i - 1] = connected[trav.j - 1] = true;
		}
	}
	delete [] connected;
	return result;
}

//main idea:
//1.it constructs based on edge.
//2.select the minimum weight edge which contains the vertex that does exits in the connected component,the loop ends when all the vertex are connected.

template<typename T,typename K>
int UndiGraph<T,K>::minedge(int source,bool *connected)
{
	MinEdge<K> trav;
	WEdge<T,K> *p = NodeTable[source - 1].adj;
	trav.i = source;
	trav.weight = this->maxweight;
	while(p != nullptr)
	{
		if(trav.weight > p->cost && connected[p->dest] == false)
		{
			trav.j = p->dest + 1;
			trav.weight = p->cost;
		}
		p = p->next;
	}
	if(trav.weight != this->maxweight)
		return trav.j;
	else
		return -1;
}

template<typename T,typename K>
void UndiGraph<T,K>::Prim(UndiGraph<T,K> &result)
{
	bool *connected = new bool[this->currentvertex];
	int i,j,mini,minj;
	for(int i = 0;i < this->currentvertex;i++)
		connected[i] = false;
	result.currentvertex = result.currentedge = 0;
	//first step:select the minimum wight edge connected with the first vertex(or another vertex)
	minj = minedge(1,connected);
	connected[0] = connected[minj - 1] = true;
	result.InsertVertex(NodeTable[0].data);
	result.InsertVertex(NodeTable[minj - 1].data);
	result.InsertEdge(1,2,GetWeight(1,minj));
	//loop
	while(result.currentvertex != this->currentvertex)
	{
		//select the minimum edge
		mini = minj = this->maxvertex;
		for(i = 1;i <= this->currentvertex;i++)
		{
			if(connected[i - 1] == true)
			{
				j = minedge(i,connected);
				if(j != -1 && GetWeight(i,j) < GetWeight(mini,minj))
				{
					mini = i;
					minj = j;
				}
			}
		}
		result.InsertVertex(NodeTable[minj - 1].data);
		result.InsertEdge(result.GetVertexPos(NodeTable[mini- 1].data),result.GetVertexPos(NodeTable[minj-1].data),GetWeight(mini,minj));
		connected[minj - 1] = true;
	}
	delete [] connected;
}

template<typename T,typename K>
void UndiGraph<T,K>::Solin(UndiGraph<T,K> &result)
{
	int i;
	WEdge<T,K> *trav;
	K travwe;
	//equal define of ufset.
	int *connected = new int[this->currentvertex];
	bool finished  = false;
	result.currentvertex = result.currentedge = 0;
	for(i = 0;i < this->currentvertex;i++)
	{
		connected[i] = -1;
		result.InsertVertex(NodeTable[i].data);
	}
	while(finished == false)
	{
		for(int i = 0;i < this->currentvertex;i++)
		{
			if(connected[i] == -1)
			{
				trav = NodeTable[i].adj;
				travwe = this->maxweight;
				while(trav != nullptr)
				{
					if(trav->cost < travwe)
					{
						travwe = trav->cost;
						connected[i] = trav->dest;
					}
					trav = trav->next;
				}
			}
			result.InsertEdge(i + 1,connected[i] + 1,travwe);
		}
		finished = true;
		for(int i = 0;i <this->currentvertex;i++)
			if(connected[i] == -1)
				finished = false;
	}
}
template<typename T,typename K>
void UndiGraph<T,K>::Rosenstiehl(UndiGraph<T,K> &result)
{
	result.currentedge = result.currentvertex = 0;
	UFSet<
}
//----------------------definition of weighted-digraph---------------
template<typename T,typename K>
DiGraph<T,K>::~DiGraph()
{
	while(this->currentvertex > 0)
		RemoveVertex(this->currentvertex - 1);
	delete [] InNodeTable;
	delete [] OutNodeTable;
}

template<typename T,typename K>
void DiGraph<T,K>::CreateGraph(const T *d,const K *w,const int &n)
{
	for(int i = 0;i < n;i++)
	{
		InsertVertex(d[2 * i]);
		InsertVertex(d[2 * i + 1]);
		InsertEdge(d[2 * i],d[2 * i + 1],w[i]);
	}
}

template<typename T,typename K>
void DiGraph<T,K>::CreateGraph(std::istream &is)
{
	T v1,v2;
	K we;
	while(is>>v1>>v2>>we)
	{
		InsertVertex(v1);
		InsertVertex(v2);
		InsertEdge(v1,v2,we);
	}
}

template<typename T,typename K>
bool DiGraph<T,K>::IsFull()
{
	int e = this->currentedge;
	int v = this->currentvertex;
	return v == this->maxvertex && e == v*(v - 1);
}

template<typename T,typename K>
T DiGraph<T,K>::GetValue(const int &i)
{
	return InNodeTable[i - 1].data;
}

template<typename T,typename K>
K DiGraph<T,K>::GetWeight(const int &v1,const int &v2)
{
	if(!this->isvalid())
		return this->maxweight;
	WEdge<T,K> *trav = OutNodeTable[v1 - 1].next;
	while(trav != nullptr && trav->dest != v2 - 1)
		trav = trav->next;
	if(trav == nullptr)
	{
		std::cout<<"the two vertex are not connected.."<<std::endl;
		return this->maxweight;
	}
	else
		return trav->cost;
}
template<typename T,typename K>
int DiGraph<T,K>::GetVertexPos(const T &v)
{
	int i;
	for(i = 0;InNodeTable[i].data != v && i < this->currentvertex;i++);
	if(InNodeTable[i].data != v)
		return -1;
	else
		return i + 1;
}

template<typename T,typename K>
int DiGraph<T,K>::GetFirstNeighbor(const int &v)
{
	if(v < 1 && v > this->currentvertex)
	{
		std::cout<<"invalid vertex"<<std::endl;
		exit(1);
	}
	WEdge<T,K> *e = OutNodeTable[v - 1].adj;
	if(e != nullptr)
		return e->dest + 1;
	else
		return -1;
}

template<typename T,typename K>
int DiGraph<T,K>::GetNextNeighbor(const int &v,const int &w)
{
	if(!this->isvalid())
		return -1;
	WEdge<T,K> *trav = OutNodeTable[v - 1].adj;
	while(trav != nullptr && trav->dest != w -1)
		trav = trav->next;
	if(trav->dest != w - 1)
	{
		std::cout<<"the two vertex are not connected"<<std::endl;
		return -1;
	}
	if(trav->next != nullptr)
		return trav->next->dest + 1;
	else
		return -1;
}
template<typename T,typename K>
bool DiGraph<T,K>::InsertVertex(const T &ver)
{
	if(this->currentvertex == this->maxvertex)
	{
		std::cout<<"the vertex array is full"<<std::endl;
		return false;
	}
	if(GetVertexPos(ver) == -1)
	{
		InNodeTable[this->currentvertex].data = ver;
		OutNodeTable[this->currentvertex].data = ver;
		this->currentvertex++;
	}
	else
		return false;
	return true;
}
template<typename T,typename K>
bool DiGraph<T,K>::InsertEdge(const int &v1,const int &v2,const K &weight)
{
	if(!this->isvalid(v1,v2))
		return false;
	WEdge<T,K> *tmpv1 = new WEdge<T,K>(v2,weight);
	WEdge<T,K> *tmpv2 = new WEdge<T,K>(v1,weight);
	WEdge<T,K> *trav = OutNodeTable[v1 - 1].adj;
	while(trav != nullptr)
	{
		if(trav->dest == v2 - 1)
		{
			std::cout<<"the edge is already existed.."<<std::endl;
			return false;
		}
		trav = trav->next;
	}
	tmpv1->next = OutNodeTable[v1 - 1].adj;
	OutNodeTable[v1 - 1].adj = tmpv1;
	tmpv2->next = InNodeTable[v2 - 1].adj;
	InNodeTable[v2 - 1].adj = tmpv2;
	this->currentedge++;
	return true;
}

template<typename T,typename K>
bool DiGraph<T,K>::RemoveEdge(const int &v1,const int &v2)
{
	if(!this->isvalid(v1,v2))
		return false;
	WEdge<T,K>*trav,pre;
	trav = OutNodeTable[v1 - 1].adj;
	pre = trav;
	while(trav->dest != v2 - 1 && trav != nullptr)
	{
		pre = trav;
		trav = trav->next;
	}
	if(trav == nullptr)
	{
		std::cout<<"the edge is not existed"<<std::endl;
		return false;
	}
	//if edge is the first neighbor
	if(pre == trav)
		OutNodeTable[v1 - 1].adj = trav->next;
	else
		pre->next = trav->next;
	delete trav;
	trav = nullptr;
	//below is the same as above,the difference is that modify the InNodeTable
	trav = InNodeTable[v2 - 1].adj;
	pre = trav;
	while(trav->dest != v1 - 1 && trav != nullptr)
	{
		pre = trav;
		trav = trav->next;
	}
	if(trav == nullptr)
	{
		std::cout<<"the edge is not existed"<<std::endl;
		return false;
	}
	//if edge is the first neighbor
	if(pre == trav)
		InNodeTable[v2 - 1].adj = trav->next;
	else
		pre->next = trav->next;
	delete trav;
	trav = nullptr;	
	this->currentedge--;
	return true;
}

template <typename T,typename K>
bool DiGraph<T,K>::RemoveVertex(const int &v1)
{
	if(v1 < 1 || v1 > this->currentvertex)
	{
		std::cout<<"the vertex is invalid"<<std::endl;
		return false;
	}
	WEdge<T,K>* trav,tmp;
	trav = OutNodeTable[v1 - 1].adj;
	while(trav != nullptr)
	{
		tmp = trav->next;
		delete trav;
		trav = tmp;
		this->currentedge--;
	}
	trav = InNodeTable[v1 - 1].adj;
	while(trav != nullptr)
	{
		tmp = trav->next;
		delete trav;
		trav = tmp;
		this->currentedge--;
	}
	this->currentvertex--;
	return true;
}

#endif
