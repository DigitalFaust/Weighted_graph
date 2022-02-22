#include<iostream>
#include<cstdlib>
using std::cout;
using std::endl;
using std::cin;

#define LAZY_INPUT

constexpr int MAXV = 100;
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
	int nedges;
	int nvertices;
	bool directed;
};

void init_graph(graph* g, bool directed);
void read_graph(graph* g, bool directed);
void insert_edge(graph* g, int x, int y, bool directed);
void insert_edge(graph* g, int x, int y, int w, bool directed);
void print_graph(graph* g);

struct set_union
{
	int p[MAXV];	// parent element
	int size[MAXV]; // number of elements in subtree i
	int n;		// number of elements in set
};

void set_union_init(set_union *s, int n);
int find(set_union* s, int x);
void union_sets(set_union* s, int s1, int s2);
bool is_same_component(set_union* s, int s1, int s2);

struct edge
{
	int x;
	int y;
	int weight;
};

void to_edge_array(graph* g, edge e[]);

int compare(const void* e1, const void* e2);
void kruskal_mst(graph* g);
void print_mst(graph* g);

int main()
{
	graph* g = new graph;
	bool directed = false;

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

	cout << "Building the minimal spanning tree...\n";
	kruskal_mst(g);
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

void read_graph(graph* g, bool directed)
{
	int m {0}, x {0}, y {0};

	init_graph(g, directed);
	cout << "Enter a number of edges: ";
	cin >> m;
	cout << "Enter a number of vertices: ";
	cin >> g->nvertices;

	for(int i = 1; i <= m; i++)
	{
		cout << "Enter vertices x and y: ";
		cin >> x >> y;
		insert_edge(g, x, y, directed);
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
		cout << i << ": ";
		p = g->edges[i];
		while(p != nullptr)
		{
			cout << p->y << " ";
			p = p->next;
		}
		cout << endl;
	}
}

void set_union_init(set_union* s, int n)
{
	for(int i = 1; i <= n; i++)
	{
		s->p[i] = i;
		s->size[i] = 1;
	}

	s->n = n;
}

int find(set_union* s, int x)
{
	if(s->p[x] == x)
		return x;
	else
		return find(s, s->p[x]);
}

void union_sets(set_union* s, int s1, int s2)
{
	int r1 = find(s, s1);
	int r2 = find(s, s2);

	if(s->size[r1] >= s->size[r2])
	{
		s->size[r1] = s->size[r1] + s->size[r2];
		s->p[r2] = r1;
	}
	else
	{
		s->size[r2] = s->size[r1] + s->size[r2];
		s->p[r1] = r2;
	}
}

bool is_same_component(set_union* s, int s1, int s2)
{
	return (find(s, s1) == find(s, s2));
}

void to_edge_array(graph* g, edge e[])
{
	edgenode* p {nullptr};
	int cnt = 1;

	for(int i = 1; i <= g->nvertices; i++)
	{
		p = g->edges[i];
		while(p != nullptr)
		{
			e[cnt].x = i;
			e[cnt].y = p->y;
			e[cnt].weight = p->weight;
			cnt++;
			p = p->next;
		}
	}
}

int compare(const void* e1, const void* e2)
{
	if((*(edge*)e1).weight > (*(edge*)e2).weight) return 1;
	if((*(edge*)e1).weight < (*(edge*)e2).weight) return -1;
	return 0;
}

void kruskal_mst(graph* g)
{
	set_union s;
	edge e[MAXV] {0};

	set_union_init(&s, g->nvertices);

	to_edge_array(g, e);
	qsort(e, 2*(g->nedges), sizeof(edge), compare);

	for(int i = 1; i < 2*(g->nedges); i++)
	{
		if(!is_same_component(&s, e[i].x, e[i].y))
		{
			cout << "[ " << e[i].x << ", " << e[i].y << "] ";
			//parent[e[i].x] = e[i].y;
			union_sets(&s, e[i].x, e[i].y);
		}
	}
}

void print_mst(graph* g)
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
