#include<iostream>
#include<limits>
#include<cmath>
#include<ctime>
using std::cout;
using std::cin;
using std::endl;

//#define RAND

const int MAXV = 100;
const int MAXINT = std::numeric_limits<int>::max();
int parent[MAXV + 1];

struct edgenode
{
	int y;
	int weight;
	edgenode* next;
};

struct graph
{
	edgenode* edges[MAXV + 1];
	int degree[MAXV + 1];
	int nvertices;
	int nedges;
	bool directed;
};

void init_graph(graph* g, bool directed);
void read_graph(graph* g);
void insert_edge(graph* g, int x, int y, bool directed);
void print_graph(graph* g);
void prim(graph* g, int start);
void print_parent(graph* g);

int main()
{
	graph* g = new graph;
	bool directed {false};
	srand(time(0));

	init_graph(g, directed);
	read_graph(g);
	cout << "The graph:\n";
	print_graph(g);

	cout << "Building minimal spanning tree: ";
	prim(g, 1);
	cout << endl;
	print_parent(g);
	cout << endl;

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
	int m {0}, x {0}, y{0};

	cout << "Enter number of edges: ";
	cin >> m;
	cout << "Enter number of vertices: ";
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
#if RAND
	p->weight = rand() % 100;
#else
	cout << "Enter weight of (" << x << ", " << y << "): ";
	cin >> p->weight;
#endif
	p->next = g->edges[x];
	g->edges[x] = p;
	g->degree[x]++;

	if(!directed)
		insert_edge(g, y, x, true);
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
			cout << "(" << p->y << ", " << p->weight << ") ";
			p = p->next;
		}
		cout << endl;
	}
}

void prim(graph* g, int start)
{
	int v {0}, w {0}, distances[MAXV + 1] {MAXINT}, min_dist {0}, weight {0};
	bool intree[MAXV + 1] {false};
	edgenode* p {nullptr};

	for(int i = 1; i <= g->nvertices; i++)
	{
		distances[i] = MAXINT;
		intree[i] = false;
		parent[i] = 0;
	}

	distances[start] = 0;
	v = start;
	while(!intree[v])
	{
		intree[v] = true;
		p = g->edges[v];
		while(p != nullptr)
		{
			w = p->y;
			weight = p->weight;
			if(!intree[w] && (distances[w] > weight))
			{
				distances[w] = weight;
				parent[w] = v;
			}
			p = p->next;
		}
		v = 1;
		min_dist = MAXINT;
		for(int i = 1; i <= g->nvertices; i++)
		{
			if(!intree[i] && (min_dist > distances[i]))
			{
				min_dist = distances[i];
				v = i;
			}
		}
	}
}

void print_parent(graph* g)
{
	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << i << " | ";
	}
	cout << endl;
	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << parent[i] << " | ";
	}
	cout << endl;
}
