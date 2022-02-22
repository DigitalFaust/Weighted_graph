#include<iostream>
#include<iomanip>
#include<limits>
using std::setw;
using std::cout;
using std::cin;
using std::endl;

#define LAZY_INPUT

const int MAXV = 100;
const int MAXINT = std::numeric_limits<int>::max();
int parent[MAXV];

struct edgenode
{
	int y;
	int weight;
	edgenode* next;
};

struct graph
{
	edgenode* edges[MAXV];
	int degree[MAXV];
	int nvertices;
	int nedges;
	bool directed;
};

void init_graph(graph* g, bool directed);
void read_graph(graph* g);
void insert_edge(graph* g, int x, int y, bool directed);
void insert_edge(graph* g, int x, int y, int w, bool directed);
void print_graph(graph* g);
void prim_mst(graph* g, int start);
void print_mst(graph* g);

int main()
{
	graph* g = new graph;
	bool directed {false};

	init_graph(g, directed);

#ifndef LAZY_INPUT
	read_graph(g, directed);
#else
	g->nvertices = 16;

	insert_edge(g, 1, 2, 1, directed);
	insert_edge(g, 1, 5, 2, directed);
	insert_edge(g, 2, 3, 18, directed);
	insert_edge(g, 2, 6, 4, directed);
	insert_edge(g, 3, 4, 20, directed);
	insert_edge(g, 3, 7, 1, directed);
	insert_edge(g, 4, 8, 4, directed);
	insert_edge(g, 5, 6, 10, directed);
	insert_edge(g, 5, 9, 5, directed);
	insert_edge(g, 6, 7, 13, directed);
	insert_edge(g, 6, 10, 6, directed);
	insert_edge(g, 7, 8, 22, directed);
	insert_edge(g, 7, 11, 11, directed);
	insert_edge(g, 8, 12, 5, directed);
	insert_edge(g, 9, 10, 11, directed);
	insert_edge(g, 9, 13, 3, directed);
	insert_edge(g, 10, 11, 4, directed);
	insert_edge(g, 10, 14, 9, directed);
	insert_edge(g, 11, 12, 23, directed);
	insert_edge(g, 11, 15, 12, directed);
	insert_edge(g, 12, 16, 9, directed);
	insert_edge(g, 13, 14, 1, directed);
	insert_edge(g, 14, 15, 9, directed);
	insert_edge(g, 15, 16, 8, directed);
#endif
	cout << "The graph:\n";
	print_graph(g);
	cout << endl;

	cout << "Building minimal spanning tree...\n";
	prim_mst(g, 1);
	print_mst(g);

	return 0;
}

void init_graph(graph* g, bool directed)
{
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for(int i = 1; i <= MAXV; i++)
	{
		g->edges[i] = nullptr;
		g->degree[i] = 0;
	}
}

void read_graph(graph* g)
{
	int x {0}, y {0}, m {0};

	cout << "Enter a number of edges: ";
	cin >> m;
	cout << "Enter a number of vertices: ";
	cin >> g->nvertices;

	for(int i = 1; i <= m; i++)
	{
		cout << "Enter vertices x and y: ";
		cin >> x >> y;
		insert_edge(g, x, y, g->directed);
	}
}

void insert_edge(graph* g, int x, int y, bool directed)
{
	edgenode* p = new edgenode;

	p->y = y;
	cout << "Enter weight of (" << x << ", " << y << "): ";
	cin >> p->weight;
	p->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x]++;

	if(!directed)
		insert_edge(g, y, x, true);
	else
		g->nedges++;
}

void insert_edge(graph* g, int x, int y, int w, bool directed)
{
	edgenode* p = new edgenode;

	p->y = y;
	p->weight = w;
	p->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x]++;

	if(!directed)
		insert_edge(g, y, x, w, true);
	else
		g->nedges++;

}

void print_graph(graph* g)
{
	edgenode* p {nullptr};

	for(int i = 1; i <= g->nvertices; i++)
	{
		p = g->edges[i];
		cout << i << ": ";
		while(p != nullptr)
		{
			cout << "[" << p->y << " : " << p->weight << "] ";
			p = p->next;
		}
		cout << endl;
	}
}

void prim_mst(graph* g, int start)
{
	bool intree[MAXV] {false};
	int distance[MAXV] {MAXINT};
	int v {0}, w {0}, weight {0}, mindist {MAXINT};
	edgenode* p {nullptr};

	for(int i = 1; i <= g->nvertices; i++)
	{
		parent[i] = -1;
		intree[i] = false;
		distance[i] = MAXINT;
	}

	v = start;
	distance[v] = 0;
	while(!intree[v])
	{
		intree[v] = true;
		p = g->edges[v];
		while(p != nullptr)
		{
			w = p->y;
			weight = p->weight;
			if(!intree[w] && (weight < distance[w]))
			{
				distance[w] = weight;
				parent[w] = v;
			}
			p = p->next;
		}

		v = 1;
		mindist = MAXINT;
		for(int i = 1; i <= g->nvertices; i++)
		{
			if(!intree[i] && (mindist > distance[i]))
			{
				mindist = distance[i];
				v = i;
			}
		}
	}
}

void print_mst(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
		cout << setw(3) << i << " | ";
	cout << endl;
	for(int i = 1; i <= g->nvertices; i++)
		cout << setw(3) << parent[i] << " | ";
	cout << endl;
}
