#include<iostream>
#include<limits>
using std::cout;
using std::endl;
using std::cin;

constexpr int MAXINT = std::numeric_limits<int>::max();

struct edgenode
{
	int y;
	int weight;
	edgenode* next;
};

class Graph
{	
	public:
		Graph();
		Graph(bool init_direct);
		void read();
		void print();
		void print_short_path(int start, int end);
	private:
		void insert_edge(int x, int y, bool directed);
		void dijkstra(int start);
		void short_path(int start, int end);

		static const int MAXV = 100;
		int parent[MAXV + 1];
		edgenode* edges[MAXV + 1];
		int degree[MAXV + 1];
		int nvertices;
		int nedges;
		bool directed;
};

int main()
{
	Graph g {true};

	g.read();
	cout << "The graph:\n";
	g.print();

	cout << "Enter a start vertex: ";
	int start {0};
	cin >> start;
	cout << "Enter an end vertex: ";
	int end {0};
	cin >> end;

	g.print_short_path(start, end);

	return 0;
}

Graph::Graph()
{
	nvertices = 0;
	nedges = 0;
	directed = false;

	for(int i = 1; i <= MAXV; i++)
	{
		this->edges[i] = nullptr;
		this->degree[i] = 0;
	}
}

Graph::Graph(bool init_direct) : Graph()
{
	directed = init_direct;
}

void Graph::read()
{
	int m {0}, x{0}, y{0};

	cout << "Enter a number of edges: ";
	cin >> m;
	cout << "Enter a number of veritces: ";
	cin >> nvertices;

	for(int i = 1; i <= m; i++)
	{
		cout << "Enter vertices x and y: ";
		cin >> x >> y;
		insert_edge(x, y, directed);
	}
}

void Graph::insert_edge(int x, int y, bool directed)
{
	edgenode* p = new edgenode;

	p->y = y;
	cout << "Enter weight of (" << x << ", " << y << "): ";
	cin >> p->weight;
	p->next = edges[x];
	edges[x] = p;
	degree[x]++;

	if(!directed)
		insert_edge(x, y, true);
	else
		nedges++;
}

void Graph::print()
{
	edgenode* p {nullptr};

	for(int i = 1; i <= nvertices; i++)
	{
		cout << i << ": ";
		p = edges[i];
		while(p != nullptr)
		{
			cout << "[" << p->y << " : " << p->weight << "] ";
			p = p->next;
		};
		cout << endl;
	}
}

void Graph::print_short_path(int start, int end)
{
	dijkstra(start);
	short_path(start, end);
	cout << endl;
}

void Graph::dijkstra(int start)
{
	bool intree[MAXV + 1];
	int distance[MAXV + 1];
	int v {0}, w{0}, weight {0}, dist {MAXINT};
	edgenode* p {nullptr};

	for(int i = 1; i <= nvertices; i++)
	{
		intree[i] = false;
		distance[i] = MAXINT;
		parent[i] = -1;
	}

	v = start;
	distance[v] = 0;
	while(!intree[v])
	{
		intree[v] = true;
		p = edges[v];
		while(p != nullptr)
		{
			w = p->y;
			weight = p->weight;

			if(distance[w] > (distance[v] + weight))
			{
				distance[w] = distance[v] + weight;
				parent[w] = v;
			}

			p = p->next;
		}

		v = 1;
		dist = MAXINT;

		for(int i = 1; i <= nvertices; i++)
		{
			if(!intree[i] && (dist > distance[i]))
			{
				dist = distance[i];
				v = i;
			}
		}
	}
}
void Graph::short_path(int start, int end)
{
	if((start == end) || (end == -1))
		cout << start << " ";
	else
	{
		short_path(start, parent[end]);
		cout << end << " ";
	}
}
