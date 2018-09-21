#ifndef _GRAPH_H
#define _GRAPH_H

#include "sys_comm.h"
#include "Queue.hpp"
#include "Stack.hpp"
#include "UFSet.hpp"
#include "Heap_Array.hpp"
#include "Forest.hpp"

#define MAXVERT 100
#define MAXWEIGHT 32767

//ps:In the Edge and WEdge object,the definition of dest is the same as the source vertex,which means they are the index of array.Remember when calling them outside,they are begin from 1.and will minus one when dealing with the vertex.
//the definition of traverse is to visit all the vertex ,while not the edge.
//abstract base class of weighted graph
template<typename T,typename K>
class WEdge
{
	public:
		WEdge(const int &d,const K &c):dest(d),cost(c),next(nullptr){}
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
template <typename K>
class AuxiEdge
{
	public:
		AuxiEdge():i(0),j(0){}
		AuxiEdge(int x,int y,K w):i(x),j(y),weight(w){}
		AuxiEdge<K>& operator=(const AuxiEdge<K> &p){i = p.i;j=p.j;weight=p.weight;return *this;}
		bool operator<=(const AuxiEdge<K> &p){return weight <= p.weight;}
		bool operator<(const AuxiEdge<K> &p){return weight < p.weight;}
		bool operator>(const AuxiEdge<K> &p){return weight > p.weight;}
		int i,j;
		K weight;
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
   /*      virtual void DFS() = 0; */
		// virtual void DFS(const T &) = 0;
		// virtual void BFS() = 0;
		/* virtual void BFS(const T &) = 0; */
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
	Edge(const int &d):dest(d),next(nullptr){}
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
		void DFS(const T &);
		void DFS();
		void BFS(const T &);
		void BFS();
   /*  virtual void DFS(const T &) override; */
		// virtual	void DFS() override;
		// virtual	void BFS(const T &) override;
		/* virtual void BFS() override; */
		//----------------application of traverse------------
		bool IsTree();
		bool IsInLoop(UndiGraph<T,K> tmp,const int &v1,const int &v2);
		K CountWeight();
		// void CreateForest(Forest<T> &result);
		//----------------Minimum-Cost Spanning Tree------
		UndiGraph<T,K> Kruskal();
		void Prim(UndiGraph<T,K> &);
		void Solin(UndiGraph<T,K> &);
		void Rosenstiehl(UndiGraph<T,K> &);
		void Dijkstra(UndiGraph<T,K> &);
		// --------------Shortest Path--------------
		void Dijkstra(const int &v0);
		void Floyd();

	private:
		WVertex<T,K> *NodeTable;

		bool removeedge(const int &v1,const int &v2);
		void dfs(const int &,bool *,const int &);
		void dfs(const int &,bool *);
		void udfs(const int &);
		void bfs(const T &);
		int minedge(const int &,bool *);
		int minedge(const int &root,UFSet<int> &connected,bool *picked,AuxiEdge<K> *branch);
};

//--------------------declaration of weighted digraph------------
template<typename T,typename K>
class DiGraph:public WGraph<T,K>
{
	public:	
		DiGraph():WGraph<T,K>()
		{
			NodeTable = new T [this->maxvertex];
			AdjMatrix = new K* [this->maxvertex];
			for(int i = 0;i < this->maxvertex;i++)
			{
				AdjMatrix[i] = new K [this->maxvertex];
				for(int j = 0; j < this->maxvertex;j++)
					AdjMatrix[i][j] = this->maxweight;
				AdjMatrix[i][i] = 0;
			}
		};
		DiGraph(int x):WGraph<T,K>(x)
		{
			NodeTable = new T [this->maxvertex];
			AdjMatrix = new K* [this->maxvertex];
			for(int i = 0;i < this->maxvertex;i++)
			{
				AdjMatrix[i] = new K [this->maxvertex];
				for(int j = 0; j < this->maxvertex;j++)
					AdjMatrix[i][j] = this->maxweight;
				AdjMatrix[i][i] = 0;
			}
		};
		DiGraph<T,K> &operator=(DiGraph<T,K> &p);
		~DiGraph();
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
		void PrintAdj();
		void DFS(const T &);
		void DFS();
		void Dijkstra(const int &v0);
		void NDijkstra();
		void Floyd();
		void TopologicalSort();
		void Topo();
		void CriticalPath();
	private:
		T *NodeTable;
		K **AdjMatrix;
		void topo(const int &,bool *,int *toposort,int &order);
		void dfs(const int &,bool *);
};
//---------------------common function-------------------------------------
template<typename T,typename K>
bool WGraph<T,K>::isvalid(const int &v1,const int &v2) const 
{
	if((v1 < 0 || v1 >= this->currentvertex) || (v2 < 0 || v2 >= this->currentvertex) || v1 == v2)
		return false;
	return true;
}
	
template<typename T>
bool Graph<T>::isvalid(const int &v1,const int &v2) const 
{
	if((v1 < 0 && v1 >= this->currentvertex) || (v2 < 0 && v2 >= this->currentvertex) || v1 == v2)
		return false;
	return true;
}

//----------------------definition of weighted-undigraph---------------
template<typename T,typename K>
UndiGraph<T,K>::~UndiGraph()
{
	int i;
	WEdge<T,K> *trav,*pre;
	for(i = 0;i < this->currentvertex;i++)
	{
		trav = NodeTable[i].adj;
		while(trav != nullptr)
		{
			pre = trav;
			trav = trav->next;
			delete pre;
			pre = nullptr;
		}
	}
	delete [] NodeTable;
}
template<typename T,typename K>		
UndiGraph<T,K>::UndiGraph(const UndiGraph<T,K> &p)
{
	NodeTable = new WVertex<T,K>[p.maxvertex];
	for(int i = 0;i < p.currentvertex;i++)
		InsertVertex(p.NodeTable[i].data);
	for(int i = 0;i < p.currentvertex;i++)
		for(int j = i + 1;j < p.currentvertex;j++)
			if(p.GetWeight(i,j) != p.maxweight)
				InsertEdge(i,j,p.GetWeight(i,j));
	
}

template<typename T,typename K>		
UndiGraph<T,K>& UndiGraph<T,K>::operator=(const UndiGraph<T,K> &p)
{
	this->~UndiGraph();
	NodeTable = new WVertex<T,K>[p.maxvertex];
	for(int i = 0;i < p.currentvertex;i++)
		InsertVertex(p.NodeTable[i].data);
	for(int i = 0;i < p.currentvertex;i++)
		for(int j = i + 1;j < p.currentvertex;j++)
			if(p.GetWeight(i,j) != p.maxweight)
				InsertEdge(i,j,p.GetWeight(i,j));
	return *this;
}

template<typename T,typename K>		
UndiGraph<T,K>& UndiGraph<T,K>::operator=(UndiGraph<T,K> &&p)
{
	this->~UndiGraph();
	NodeTable = new WVertex<T,K>[p.maxvertex];
	for(int i = 0;i < p.currentvertex;i++)
		InsertVertex(p.NodeTable[i].data);
	for(int i = 0;i < p.currentvertex;i++)
		for(int j = i + 1;j < p.currentvertex;j++)
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
		InsertEdge(GetVertexPos(d[2 * i]),GetVertexPos(d[2 * i + 1]),w[i]);
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
	return NodeTable[i].data;
}

template<typename T,typename K>
K UndiGraph<T,K>::GetWeight(const int &v1,const int &v2) const 
{
	if(!this->isvalid(v1,v2))
		return this->maxweight;
	WEdge<T,K> *trav = NodeTable[v1].adj;
	while(trav != nullptr && trav->dest != v2)
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
		return i;
}

template<typename T,typename K>
int UndiGraph<T,K>::GetFirstNeighbor(const int &v)
{
	if(v < 0 && v >= this->currentvertex)
		return -1;
	WEdge<T,K> *e = NodeTable[v].adj;
	if(e != nullptr)
		return e->dest;
	else
		return -1;
}

template<typename T,typename K>
int UndiGraph<T,K>::GetNextNeighbor(const int &v,const int &w)
{
	if(!this->isvalid(v,w))
		return -1;
	WEdge<T,K> *trav = NodeTable[v].adj;
	while(trav != nullptr && trav->dest != w)
		trav = trav->next;
	if(trav->dest != w)
	{
		std::cout<<"the two vertex are not connected"<<std::endl;
		return -1;
	}
	if(trav->next != nullptr)
		return trav->next->dest;
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
	WEdge<T,K> *trav = NodeTable[v1].adj;
	while(trav != nullptr)
	{
		if(trav->dest == v2)
		{
			std::cout<<"the edge is already existed.."<<std::endl;
			return false;
		}
		trav = trav->next;
	}
	tmpv1->next = NodeTable[v1].adj;
	NodeTable[v1].adj = tmpv1;
	tmpv2->next = NodeTable[v2].adj;
	NodeTable[v2].adj = tmpv2;
	this->currentedge++;
	return true;
}

template<typename T,typename K>
bool UndiGraph<T,K>::removeedge(const int &v1,const int &v2)
{
	WEdge<T,K> *trav = NodeTable[v1].adj;
	WEdge<T,K> *pre = trav;
	while(trav->dest != v2 && trav != nullptr)
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
		NodeTable[v1].adj = trav->next;
	else
		pre->next = trav->next;
	delete trav;
	trav = nullptr;
	return true;
}
template<typename T,typename K>
bool UndiGraph<T,K>::RemoveEdge(const int &v1,const int &v2)
{
	int v,w;
	v = v1;
	w = v2;
	if(!this->isvalid(v1,v2) && GetWeight(v1,v2) == this->maxweight)
		return false;
	removeedge(v,w);
	removeedge(w,v);
	this->currentedge--;
	return true;
}

template <typename T,typename K>
bool UndiGraph<T,K>::RemoveVertex(const int &v1)
{
	WEdge<T,K> *trav,*ptrav;
	if(v1 < 0 || v1 >= this->currentvertex)
	{
		std::cout<<"the vertex is invalid"<<std::endl;
		return false;
	}
	while(NodeTable[v1].adj != nullptr)
		RemoveEdge(v1,NodeTable[v1].adj->dest);
	if(v1 == this->currentvertex - 1)
	{
		this->currentvertex--;
		return true;
	}
	else
	{
		NodeTable[v1] = NodeTable[this->currentvertex - 1];
		trav = NodeTable[v1].adj;
		while(trav != nullptr)
		{
			ptrav = NodeTable[trav->dest].adj;
			while(ptrav->dest != this->currentvertex - 1)
				ptrav = ptrav->next;
			ptrav->dest = v1;
			trav = trav->next;
		}
		this->currentvertex--;
		return true;
	}
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
	std::cout<<NodeTable[loc].data<<" ";
	visited[loc] = true;
	q.Enqueue(loc);
	while(!q.IsEmpty())
	{
		q.Dequeue(loc);
		trav = GetFirstNeighbor(loc);
		while(trav != -1)
		{
			if(visited[trav] == false)
			{
				visited[trav] = true;
				std::cout<<NodeTable[trav].data<<" ";
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
	for(int i = 0;i < this->currentvertex;i++)
		visited[i] = false;
	dfs(GetVertexPos(v),visited);
	for(int i = 0;i < this->currentvertex;i++)
		if(visited[i] == false)
			dfs(i,visited);
	std::cout<<std::endl;
	delete [] visited;
}

template<typename T,typename K>
void UndiGraph<T,K>::DFS()
{
	udfs(0);
	std::cout<<std::endl;
}

template<typename T,typename K>
void UndiGraph<T,K>::dfs(const int &v,bool visited[],const int &flag)
{
	if(flag == 0)
		std::cout<<NodeTable[v].data<<" ";
	visited[v] = true;
	int w = GetFirstNeighbor(v);
	while(w != -1)
	{
		if(visited[w] == false)
			dfs(w,visited,flag);
		w = GetNextNeighbor(v,w);
	}
}

template<typename T,typename K>
void UndiGraph<T,K>::dfs(const int &v,bool visited[])
{
	visited[v] = true;
	int w = GetFirstNeighbor(v);
	while(w != -1)
	{
		if(visited[w] == false)
			dfs(w,visited);
		w = GetNextNeighbor(v,w);
	}
}

template<typename T,typename K>
void UndiGraph<T,K>::udfs(const int &v)
{
	bool *visited = new bool[this->currentvertex];
	Stack<int> sq;
	int tp,trav = v;
	std::memset(visited,false,sizeof(bool)*this->currentvertex);
	//designate the first node or it can be one loop while not two.
	sq.Push(trav);
	visited[trav] = true;
	while(!sq.IsEmpty())
	{
		// sq.Traverse();
		sq.Pop(trav);
		std::cout<<NodeTable[trav].data<<" ";
		tp = GetFirstNeighbor(trav);
		while(tp != -1)
		{
			if(visited[tp] == false)
			{
				sq.Push(tp);
				visited[tp] = true;
			}
			tp = GetNextNeighbor(trav,tp);
		}
	}
	for(int i = 0;i < this->currentvertex;i++)
		if(visited[i] == false)
		{
			visited[i] = true;
			while(!sq.IsEmpty())
			{
				// sq.Traverse();
				sq.Pop(trav);
				std::cout<<NodeTable[i].data<<" ";
				tp = GetFirstNeighbor(i);
				while(tp != -1)
				{
					if(visited[tp] == false)
					{
						sq.Push(tp);
						visited[tp] = true;
					}
					tp = GetNextNeighbor(i,tp);
				}
			}	
		}
	delete [] visited;
}

template<typename T,typename K>
bool UndiGraph<T,K>::IsTree()
{
	if(this->currentedge + 1 != this->currentvertex)
		return false;
	bool *visited = new bool[this->currentvertex];
	for(int i = 0;i < this->currentvertex;i++)
		visited[i] = false;
	dfs(0,visited,1);
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
bool UndiGraph<T,K>::IsInLoop(UndiGraph<T,K> tmp,const int &v1,const int &v2)
{
	
}
template<typename T,typename K>
K UndiGraph<T,K>::CountWeight()
{
	K result = 0;
	for(int i = 0;i < this->currentvertex;i++)	
		for(int j = i + 1;j < this->currentvertex;j++)
			if(GetWeight(i,j) != this->maxweight)
				result += GetWeight(i,j);
	return result;
}

/*
 * template<typename T,typename K>
 * void UndiGraph<T,K>::CreateForest(Forest<T> &result)
 * {
 * 
 * }
 */

//----------------MST----------------------------------


//Main idea of Kruskal: 
//it is suitable from the sparse graph,based on vertex.
//1.bulid a vertex set contains all the vertex;
//2.order edges in weight ascending order;
//3.select edge from the edge set,if the head and tail vertex is already connected,then abondan the edge,continuing the process until the edge num of result is vertex minus 1.
template<typename T,typename K>
UndiGraph<T,K> UndiGraph<T,K>::Kruskal()
{
	int i,j;
	UFSet<int> connected(this->currentvertex);
	MinHeap<AuxiEdge<K>> h;
	AuxiEdge<K> trav;
	UndiGraph<T,K> result;
	//construct a graph with all vertexs and zero edge.
	for(i = 0;i < this->currentvertex;i++)
		result.InsertVertex(NodeTable[i].data);
	//build the minheap of edges.
	for(i = 0;i < this->currentvertex;i++)
	{
		for(j = i + 1; j < this->currentvertex;j++)
			if(GetWeight(i,j) != this->maxweight)
				h.Insert(AuxiEdge<K>(i,j,GetWeight(i,j)));
	}
	//the main process,use ufset is more concise.
	while(!connected.IsOne())
	{
		h.Remove(trav);
		if(connected.FindRoot(trav.i) != connected.FindRoot(trav.j))
		{
			result.InsertEdge(trav.i,trav.j,trav.weight);
			connected.Merge(trav.i,trav.j);
		}
	}
	return result;
}

//main idea:
//1.it constructs based on edge.
//2.select the minimum weight edge which contains the vertex that does exits in the connected component,the loop ends when all the vertex are connected.

template<typename T,typename K>
int UndiGraph<T,K>::minedge(const int &source,bool *connected)
{
	AuxiEdge<K> trav;
	WEdge<T,K> *p = NodeTable[source].adj;
	trav.i = source;
	trav.weight = this->maxweight;
	while(p != nullptr)
	{
		if(trav.weight > p->cost && connected[p->dest] == false)
		{
			trav.j = p->dest;
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
int UndiGraph<T,K>::minedge(const int &root,UFSet<int> &connected,bool *picked,AuxiEdge<K> *branch)
{
	int i,j,k;
	k = -1;
	for(i = 0;i < this->currentvertex;i++)
	{
		if(connected.FindRoot(i) == root)
		{
			for(j = 0;j < this->currentedge;j++)
			{
				if((branch[j].i == i || branch[j].j == i) && picked[j] == false)
				{
					if(k == -1)
						k = j;
					else
					{
						if(branch[k].weight > branch[j].weight)
							k = j;
					}
				}
			}
		}
	}
	return k;
}

template<typename T,typename K>
void UndiGraph<T,K>::Prim(UndiGraph<T,K> &result)
{
	bool *connected = new bool [this->currentvertex];
	int i,j,mini,minj;
	for(int i = 0;i < this->currentvertex;i++)
		connected[i] = false;
	result.currentvertex = result.currentedge = 0;
	//first step:select the minimum weight edge connected with the first vertex(or another vertex)
	minj = minedge(0,connected);
	connected[0] = connected[minj] = true;
	result.InsertVertex(NodeTable[0].data);
	result.InsertVertex(NodeTable[minj].data);
	//because the NodeTable of result is builded from empty,now it contains two vertex.
	result.InsertEdge(0,1,GetWeight(0,minj));
	while(result.currentvertex != this->currentvertex)
	{
		mini = minj = this->maxvertex;
		//select the minimum edge
		for(i = 0;i < this->currentvertex;i++)
		{
			if(connected[i] == true)
			{
				j = minedge(i,connected);
				if(j != -1 && GetWeight(i,j) < GetWeight(mini,minj))
				{
					mini = i;
					minj = j;
				}
			}
		}
		result.InsertVertex(NodeTable[minj].data);
		result.InsertEdge(result.GetVertexPos(NodeTable[mini].data),result.GetVertexPos(NodeTable[minj].data),GetWeight(mini,minj));
		connected[minj] = true;
	}
	delete [] connected;
}

template<typename T,typename K>
void UndiGraph<T,K>::Solin(UndiGraph<T,K> &result)
{
	int i,j,k;
	//connected component
	UFSet<int> connected(this->currentvertex);
	//mark edge have been picked or not
	bool *picked = new bool [this->currentedge];
	//transform all the wedge to a auxiedge array
	AuxiEdge<K> *branch = new AuxiEdge<K> [this->currentedge];
	//temporary container for edge picked each round.
	int *pick = new int [this->currentedge];
	int *root = new int [this->currentvertex];
	result.currentvertex = result.currentedge = 0;
	//init the result vertex forest(equally)
	for(i = 0;i < this->currentvertex;i++)
		result.InsertVertex(NodeTable[i].data);
	std::memset(picked,false,this->currentedge * sizeof(bool));
	//transfer edge
	for(i = 0,k = 0;i < this->currentvertex;i++)
		for(j = i + 1;j < this->currentvertex;j++)
			if(GetWeight(i,j) != this->maxweight)
				branch[k++] = AuxiEdge<K>(i,j,GetWeight(i,j));
	while(!connected.IsOne())
	{
		j = connected.CountRoot(root);
		for(i = 0; i < j;i++)
			pick[i] = minedge(root[i],connected,picked,branch);
		//here can not combine the two loop
		for(i = 0; i < j;i++)
		{
			picked[pick[i]] = true;
			if(result.GetWeight(branch[pick[i]].i,branch[pick[i]].j) == this->maxweight)
			{
				result.InsertEdge(branch[pick[i]].i,branch[pick[i]].j,branch[pick[i]].weight);
				connected.Merge(branch[pick[i]].i,branch[pick[i]].j);
			}
		}
	}
	delete [] branch;
	delete [] picked;
	delete [] pick;
	delete [] root;
}

template<typename T,typename K>
void UndiGraph<T,K>::Rosenstiehl(UndiGraph<T,K> &result)
{
	int i,j;
	AuxiEdge<K> trav;
	MaxHeap<AuxiEdge<K>> h;
	bool *visited = new bool[this->currentvertex];
	result = *this;
	for(i = 0;i < this->currentvertex;i++)
		for(j = i + 1; j < this->currentvertex;j++)
			if(GetWeight(i,j) != this->maxweight)
				h.Insert(AuxiEdge<K>(i,j,GetWeight(i,j)));
	while(!result.IsTree())
	{
		std::memset(visited,false,sizeof(bool) * this->currentvertex);
		h.Remove(trav);
		result.RemoveEdge(trav.i,trav.j);	
		result.dfs(0,visited,1);
		if(visited[trav.i] != visited[trav.j])
			result.InsertEdge(trav.i,trav.j,trav.weight);
	}
	delete [] visited;
}

//---------------SP-------------------------------
template<typename T,typename K>
void UndiGraph<T,K>::Dijkstra(const int &v0)
{
	bool *S = new bool [this->currentvertex];
	K *dist = new K [this->currentvertex];
	int *path = new int [this->currentvertex];
	int *tmp = new int [this->currentvertex];
	int i,j,k,u;
	K w,min;
	for(i = 0;i < this->currentvertex;i++)
	{
		dist[i] = GetWeight(v0,i);
		S[i] = false;
		if(i != v0 && dist[i] < this->maxweight)
			path[i] = v0;
		else
			path[i] = -1;
	}
	S[v0] = true;
	dist[v0] = 0;
	for(i = 0;i < this->currentvertex - 1;i++)
	{
		min = this->maxweight;
		u = v0;
		for(j = 0;j < this->currentvertex;j++)
			if(S[j] == false && dist[j] < min)
				u = j,min = dist[j];
		S[u] = true;
		for(k = 0;k < this->currentvertex;k++)
		{
			w = GetWeight(u,k);
			if(S[k] == false && w < this->maxweight && dist[u] + w < dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	for(i = 0;i < this->currentvertex;i++)
	{
		if(i != v0)
		{
			std::cout<<NodeTable[v0].data<<" "<<NodeTable[i].data<<"\t";
			for(j = i,k = 0;path[j] != v0;j = path[j])
				tmp[k++] = j;
			tmp[k] = j;
			tmp[++k] = v0;
			while(k >= 0)
				std::cout<<NodeTable[tmp[k--]].data<<" ";
			std::cout<<'\t'<<dist[i]<<std::endl;
		}
	}
	delete [] S;
	delete [] dist;
	delete [] path;
	delete [] tmp;
}
//the method of solving every pair of nodes:
//1.call n times of Dijkstra
//2.Floyd.
//the differences between 1 and 2 is that:

	
template<typename T,typename K>
void UndiGraph<T,K>::Floyd()
{
	
}

//----------------------definition of weighted-digraph---------------
template<typename T,typename K>
DiGraph<T,K>::~DiGraph()
{
	if(NodeTable != nullptr)
		delete [] NodeTable;
	if(AdjMatrix != nullptr)
	{
		for(int i = 0;i < this->maxvertex;i++)
			if(AdjMatrix[i] != nullptr)
				delete [] AdjMatrix[i];
		delete [] AdjMatrix;
	}
}

template<typename T,typename K>
DiGraph<T,K> & DiGraph<T,K>::operator=(DiGraph<T,K> &p)
{
	this->~DiGraph();
	this->currentedge = p.currentedge;
	this->currentvertex = p.currentvertex;
	this->maxvertex = p.maxvertex;
	this->maxweight = p.maxweight;
	NodeTable = new T [p.maxvertex];
	AdjMatrix = new K* [p.maxvertex];
	for(int i = 0;i < p.maxvertex;i++)
	{
		AdjMatrix[i] = new K [p.maxvertex];
		for(int j = 0;j < p.currentvertex;j++)
			AdjMatrix[i][j] = p.AdjMatrix[i][j];
	}
	return *this;
}
template<typename T,typename K>
void DiGraph<T,K>::CreateGraph(const T *d,const K *w,const int &nd,const int &nw)
{
	for(int i = 0;i < nd;i++)
		InsertVertex(d[i]);
	for(int i = 0;i < nw;i++)
		InsertEdge(GetVertexPos(d[2 * i]),GetVertexPos(d[2 * i + 1]),w[i]);
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
	return NodeTable[i];
}

template<typename T,typename K>
K DiGraph<T,K>::GetWeight(const int &v1,const int &v2) const
{
	return AdjMatrix[v1][v2];
}

template<typename T,typename K>
int DiGraph<T,K>::GetVertexPos(const T &v)
{
	int i;
	for(i = 0;NodeTable[i] != v && i < this->currentvertex;i++);
	if(NodeTable[i] != v)
		return -1;
	else
		return i;
}

template<typename T,typename K>
int DiGraph<T,K>::GetFirstNeighbor(const int &v)
{
	int i;
	if(v < 0 && v >= this->currentvertex)
	{
		std::cout<<"invalid vertex"<<std::endl;
		exit(1);
	}
	for(i = 0;i < this->maxvertex;i++)
		if(i != v && AdjMatrix[v][i] != this->maxweight)
			return i;
	return -1;
}

template<typename T,typename K>
int DiGraph<T,K>::GetNextNeighbor(const int &v,const int &w)
{
	int i;
	if(!this->isvalid(v,w))
		return -1;
	for(i = w + 1;i < this->maxvertex;i++)
		if(AdjMatrix[v][i] != this->maxweight)
			return i;
	return -1;
}

template<typename T,typename K>
void DiGraph<T,K>::PrintAdj()
{
	for(int i = 0;i < this->currentvertex;i++)
	{
		for(int j = 0;j < this->currentvertex;j++)
		{
			if(AdjMatrix[i][j] == this->maxweight)
				std::cout<<"∞"<<" ";
			else
				std::cout<<AdjMatrix[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
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
		NodeTable[this->currentvertex++] = ver;
		AdjMatrix[GetVertexPos(ver)][GetVertexPos(ver)] = 0;
	}
	else
	{
		// std::cout<<"The Vertex"<<ver<<"is already existed.."<<std::endl;
		return false;
	}
	return true;
}
template<typename T,typename K>
bool DiGraph<T,K>::InsertEdge(const int &v1,const int &v2,const K &weight)
{
	if(!this->isvalid(v1,v2))
		return false;
	if(AdjMatrix[v1][v2] != this->maxweight)
	{
		// std::cout<<"the edge is occuped.."<<std::endl;
		return false;
	}
	AdjMatrix[v1][v2] = weight;
	this->currentedge++;
	return true;
}

template<typename T,typename K>
bool DiGraph<T,K>::RemoveEdge(const int &v1,const int &v2)
{
	if(!this->isvalid(v1,v2))
		return false;
	if(GetWeight(v1,v2) == this->maxweight)
	{
		std::cout<<"there is no edge between"<<NodeTable[v1]<<"and"<<NodeTable[v2]<<"to remove.."<<std::endl;
		return false;
	}
	AdjMatrix[v1][v2] = this->maxweight;
	this->currentedge--;
	return true;
}

template <typename T,typename K>
bool DiGraph<T,K>::RemoveVertex(const int &v1)
{
	int i;
	if(v1 < 0 || v1 >= this->currentvertex)
	{
		std::cout<<"the vertex is invalid"<<std::endl;
		return false;
	}
	for(i = 0;i < this->currentvertex;i++)
	{
		if(AdjMatrix[v1][i] != this->maxweight)
			this->currentedge--;
		AdjMatrix[v1][i] = AdjMatrix[this->currentvertex - 1][i];
	}
	NodeTable[v1] = NodeTable[this->currentvertex - 1];
	this->currentvertex--;
	return true;
}

template<typename T,typename K>
void DiGraph<T,K>::Dijkstra(const int &v0)
{
	//S for the mark the path of vertex already found,dist for recording the shortest distance,path for recording the shortest path,tmp for traverse.
	bool *S = new bool [this->currentvertex];
	K *dist = new K [this->currentvertex];
	int *path = new int [this->currentvertex];
	int *tmp = new int [this->currentvertex];
	int i,j,k,u;
	K w,min;
	//init the array.if there is a direct road from v0 to i,then fill with it at the begining,else -1.
	for(i = 0;i < this->currentvertex;i++)
	{
		dist[i] = GetWeight(v0,i);
		S[i] = false;
		if(i != v0 && dist[i] < this->maxweight)
			path[i] = v0;
		else
			path[i] = -1;
	}
	S[v0] = true;
	dist[v0] = 0;
	//main procedure
	for(i = 0;i < this->currentvertex - 1;i++)
	{
		min = this->maxweight;
		u = v0;
		//check direct path
		for(j = 0;j < this->currentvertex;j++)
			if(S[j] == false && dist[j] < min)
				u = j,min = dist[j];
		S[u] = true;
		//check indirect path
		for(k = 0;k < this->currentvertex;k++)
		{
			w = GetWeight(u,k);
			if(S[k] == false && w < this->maxweight && dist[u] + w < dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	//output
	for(i = 0;i < this->currentvertex;i++)
	{
		if(i != v0)
		{
			std::cout<<NodeTable[v0]<<" "<<NodeTable[i]<<"\t";
			if(dist[i] != this->maxweight)
			{
				for(j = i,k = 0;path[j] != v0;j = path[j])
					tmp[k++] = j;
				tmp[k] = j;
				tmp[++k] = v0;
				while(k >= 0)
					std::cout<<NodeTable[tmp[k--]]<<" ";
			}
			std::cout<<'\t'<<dist[i]<<std::endl;
		}
	}
	delete [] S;
	delete [] dist;
	delete [] path;
	delete [] tmp;
}

template<typename T,typename K>
void DiGraph<T,K>::NDijkstra()
{
	for(int i = 0;i < this->currentvertex;i++)
		Dijkstra(i);
}

template<typename T,typename K>
void DiGraph<T,K>::Floyd()
{
	K **dist;
	int **path,**tmp;
	int i,j,k,l;
	dist = new K * [this->currentvertex];
	path = new int * [this->currentvertex];
	tmp = new int * [this->currentvertex];
	for(i = 0;i < this->currentvertex;i++)
	{
		dist[i] = new K [this->currentvertex];
		path[i] = new int [this->currentvertex];
		tmp[i] = new int [this->currentvertex];
	}
	//init
	for(i = 0;i < this->currentvertex;i++)
		for(j = 0;j < this->currentvertex;j++)
		{
			dist[i][j] = GetWeight(i,j);
			if(dist[i][j] != this->maxweight && i != j)
				path[i][j] = i;
			else
				path[i][j] = 0;
		}
	//main
	for(i = 0;i < this->currentvertex;i++)
		for(j = 0;j < this->currentvertex;j++)
			for(k = 0;k < this->currentvertex;k++)
			{
				if(dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
			}
	//output	
	for(i = 0;i < this->currentvertex;i++)
	{
		for(j = 0;j < this->currentvertex;j++)
			if(j != i)
			{
				std::cout<<NodeTable[i]<<" "<<NodeTable[j]<<"\t";
				if(dist[i][j] != this->maxweight)
				{
					for(k = j,l = 0;path[i][k] != i;k = path[i][k])
						tmp[i][l++] = k;
					tmp[i][l] = k;
					tmp[i][++l] = i;
					while(l >= 0)
						std::cout<<NodeTable[tmp[i][l--]]<<" ";
				}
				std::cout<<'\t'<<dist[i][j]<<std::endl;
			}
		std::cout<<std::endl;
	}
	for(i = 0;i < this->currentvertex;i++)
	{
		delete [] dist[i];
		delete [] path[i];
		delete [] tmp[i];
	}
	delete [] dist;
	delete [] path;
	delete [] tmp;
}

template<typename T,typename K>
void DiGraph<T,K>::TopologicalSort()
{
	Stack<int> sn;
	int i,j,k,count,trav;
	DiGraph<T,K> tmp;
	tmp = *this;
	//init stack,push the 0 in-degree vertex.
	for(i = 0;i < this->currentvertex;i++)
	{
		for(j = 0,k = 0;j < this->currentvertex;j++)
		{
			if(i != j)
			{
				if(AdjMatrix[j][i] != this->maxweight)
					k++;
			}
		}
		if(k == 0)
			sn.Push(i);
	}
	count = 0;
	while(!sn.IsEmpty())
	{
		sn.Pop(trav);
		std::cout<<NodeTable[trav]<<" ";
		count++;
		//update stack after pop the vertex.
		for(j = 0;j < this->currentvertex;j++)
		{
			if(trav != j && AdjMatrix[trav][j] != this->maxweight)
			{
				//delete the edge connected with the deleted vertex.
				tmp.AdjMatrix[trav][j] = this->maxweight;
				//re-count the 0 in-degree vertexs.if there is a loop in the graph,then it must stop at the the remnant,the count will be less than vertxnum.
				for(i = 0,k = 0;i < this->currentvertex;i++)
					if(i != j)
						if(tmp.AdjMatrix[i][j] != this->maxweight)
							k++;
				if(k == 0)
					sn.Push(j);
			}
		}
	}
	std::cout<<std::endl;
	if(count < this->currentvertex)
		std::cout<<"Loop!"<<std::endl;
	else
		std::cout<<"No loop!"<<std::endl;
}

template<typename T,typename K>
void DiGraph<T,K>::CriticalPath()
{
	int i,j,k,n;
	K Ae,Al,w,*Ve,*Vl;
	n = this->currentvertex;
	Ve = new K [n];
	Vl = new K [n];
	//init Ve,Vl.
	for(i = 0;i < n;i++)
		Ve[i] = 0,Vl[i] = 0;
	//count Ve.
	for(i = 0;i < n;i++)
	{
		j = GetFirstNeighbor(i);
		while(j != -1)
		{
			w = GetWeight(i,j);
			if(Ve[i] + w > Ve[j])
				Ve[j] = Ve[i] + w;
			j = GetNextNeighbor(i,j);
		}
	}
	//print the martix.
	PrintAdj();
	for(i = 0;i < n;i++)
		std::cout<<Ve[i]<<" ";
	std::cout<<std::endl;
	Vl[n - 1] = Ve[n - 1];
	for(j = n - 2;j > 0;j--)
	{
		k = GetFirstNeighbor(j);
		w = GetWeight(j,k);
		if(Vl[j] == 0)
			Vl[j] = Vl[k] - w;
		while(k != -1)
		{
			w = GetWeight(j,k);
			if(Vl[k] - w < Vl[j])
				Vl[j] = Vl[k] - w;
			k = GetNextNeighbor(j,k);
		}
	}
	for(i = 0;i < n;i++)
		std::cout<<Vl[i]<<" ";
	std::cout<<std::endl;
	for(i = 0;i < n;i++)
	{
		j = GetFirstNeighbor(i);
		while(j != -1)
		{
			Ae = Ve[i];
			Al = Vl[j] - GetWeight(i,j);
			if(Ae == Al)
				std::cout<<"<"<<GetValue(i)<<","<<GetValue(j)<<">"<<"is critical incident"<<std::endl;
			j = GetNextNeighbor(i,j);
		}
	}
	delete [] Vl;
	delete [] Ve;
}

template<typename T,typename K>
void DiGraph<T,K>::topo(const int &v,bool visited[],int *toposort,int &order)
{
	visited[v] = true;
	for(int w = GetFirstNeighbor(v);w != -1;w = GetNextNeighbor(v,w))
		if(visited[w] == false)
			topo(w,visited,toposort,order);
	toposort[order--] = v;
	std::cout<<(order + 2)<<NodeTable[v]<<" ";
}

template<typename T,typename K>
void DiGraph<T,K>::Topo()
{
	int *path,time,order,v,start;
	bool *visited;
	visited = new bool [this->currentvertex];
	path = new int [this->currentvertex];
	std::memset(path,-1,sizeof(int) * this->currentvertex);
	std::memset(visited,false,sizeof(bool) * this->currentvertex);
	time = 0;
	order = this->currentvertex - 1;
	//loop for startvertex
	for(v = 0,start = -1;v < this->currentvertex && start == -1;v++)
	{
		start = v;
		for(int i = 0;i < this->currentvertex;i++)
			if(AdjMatrix[i][start] != 0 && AdjMatrix[i][start] != this->maxweight)
				start = -1;
	}
	if(start == -1)
	{
		std::cout<<"Loop!"<<std::endl;
		return;
	}
	//main process
	topo(start,visited,path,order);
	std::cout<<std::endl;
	// topo(start,visited,finishtime,time,path,order);
	//ouput
	for(int i = 0;i < this->currentvertex;i++)
		std::cout<<NodeTable[path[i]]<<" ";
	std::cout<<std::endl;
	delete [] visited;
	delete [] path;
}

template<typename T,typename K>
void DiGraph<T,K>::DFS(const T &v)
{
	bool *visited = new bool[this->currentvertex];
	for(int i = 0;i < this->currentvertex;i++)
		visited[i] = false;
	dfs(GetVertexPos(v),visited);
	for(int i = 0;i < this->currentvertex;i++)
		if(visited[i] == false)
			dfs(i,visited);
	std::cout<<std::endl;
	delete [] visited;
}

/*
 * template<typename T,typename K>
 * void DiGraph<T,K>::DFS()
 * {
 *     dfs(0,);
 *     std::cout<<std::endl;
 * }
 */

template<typename T,typename K>
void DiGraph<T,K>::dfs(const int &v,bool visited[])
{
	visited[v] = true;
	std::cout<<NodeTable[v]<<" ";
	int w = GetFirstNeighbor(v);
	while(w != -1)
	{
		if(visited[w] == false)
			dfs(w,visited);
		w = GetNextNeighbor(v,w);
	}
}
#endif
