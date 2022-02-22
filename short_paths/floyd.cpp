#include<iostream>
#include<limits>
#include<iomanip>
using std::setw;
using std::cout;
using std::cin;
using std::endl;

//#define LAZY_INPUT_1
#define LAZY_INPUT_2 1

constexpr int MAXV = 100;
constexpr int MAXINT = std::numeric_limits<int>::max();

struct adjacency_matrix
{
	int weight[MAXV + 1][MAXV + 1];
	int nvertices;
	adjacency_matrix()
	{
		for(int i = 1; i <= MAXV; i++)
		{
			for(int j = 1; j <= MAXV; j++)
			{
				if(i == j)
					weight[i][j] = 0;
				else
					weight[i][j] = MAXINT;
			}
		}
		nvertices = 0;
	}
};

class Graph
{
	public:
		Graph();
		Graph(bool init_direct);
		void read();
		void print();
		void floyd();
		void floyd(int limit);
		void insert_edge(int x, int y, int w);
		void set_nvertices(int n);
	private:
		void insert_edge(int x, int y);
		adjacency_matrix* g;
		bool directed;
};

int main()
{
	Graph g(false);

#ifdef LAZY_INPUT_1

	g.set_nvertices(10);

	g.insert_edge(1, 2, 6);
	g.insert_edge(1, 4, 4);
	g.insert_edge(1, 9, 9);
	g.insert_edge(2, 3, 3);
	g.insert_edge(2, 4, 3);
	g.insert_edge(2, 5, 1);
	g.insert_edge(3, 5, 2);
	g.insert_edge(3, 6, 2);
	g.insert_edge(4, 5, 4);
	g.insert_edge(4, 7, 6);
	g.insert_edge(5, 6, 8);
	g.insert_edge(5, 7, 6);
	g.insert_edge(5, 8, 7);
	g.insert_edge(6, 8, 11);
	g.insert_edge(7, 8, 3);
	g.insert_edge(7, 9, 2);
	g.insert_edge(7, 10, 2);
	g.insert_edge(8, 10, 4);
	g.insert_edge(9, 10, 1);

#elif LAZY_INPUT_2

	g.set_nvertices(16);

	g.insert_edge(1, 2, 1);
	g.insert_edge(1, 5, 2);
	g.insert_edge(2, 3, 18);
	g.insert_edge(2, 6, 4);
	g.insert_edge(3, 7, 1);
	g.insert_edge(3, 4, 20);
	g.insert_edge(4, 8, 4);
	g.insert_edge(5, 6, 10);
	g.insert_edge(5, 9, 5);
	g.insert_edge(6, 7, 13);
	g.insert_edge(6, 10, 6);
	g.insert_edge(7, 8, 22);
	g.insert_edge(7, 11, 11);
	g.insert_edge(8, 12, 5);
	g.insert_edge(9, 10, 11);
	g.insert_edge(9, 13, 5);
	g.insert_edge(10, 11, 4);
	g.insert_edge(10, 14, 9);
	g.insert_edge(11, 12, 23);
	g.insert_edge(11, 15, 12);
	g.insert_edge(12, 16, 9);
	g.insert_edge(13, 14, 1);
	g.insert_edge(14, 15, 9);
	g.insert_edge(15, 16, 8);

#else
	g.read();
#endif

	g.print();
	
	cout << "\nCalculating the shortest paths matrix...\n";
	//g.floyd();
	int k {0};
	cout << "Enter k: ";
	cin >> k;
	g.floyd(k);
	g.print();

	return 0;
}

Graph::Graph()
{
	g = new adjacency_matrix();
	directed = true;
}

Graph::Graph(bool init_direct) : Graph()
{
	directed = init_direct;
}

void Graph::read()
{
	int m {0}, x{0}, y{0};
	cout << "Enter a number of vertices: ";
	cin >> g->nvertices;
	cout << "Enter a number of edges: ";
	cin >> m;

	for(int i = 1; i <= m; i++)
	{
		cout << "Enter vertices x and y: ";
		cin >> x >> y;
		insert_edge(x, y);
	}
}

void Graph::insert_edge(int x, int y)
{
	cout << "Enter weight of (" << x << ", " << y << "): ";
	cin >> g->weight[x][y];
}

void Graph::insert_edge(int x, int y, int w)
{
	g->weight[x][y] = w;

	if(!directed)
		g->weight[y][x] = w;
}

void Graph::print()
{
	cout << "   ";
	for(int i = 1; i <= g->nvertices; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "  ";
	for(int i = 1; i <= g->nvertices; i++)
		cout << "---";
	cout << endl;
	for(int i = 1; i <= g->nvertices; i++)
	{
		cout << setw(2) << i << "|";
		for(int j = 1; j <= g->nvertices; j++)
		{
			if(g->weight[i][j] == MAXINT)
				cout << setw(3) << "#";
			else
				cout << setw(3) << g->weight[i][j];
		}
		cout << endl;
	}
}

void Graph::floyd()
{
	int through_k {0};

	for(int k = 1; k <= g->nvertices; k++)
	{
		for(int i = 1; i <= g->nvertices; i++)
		{
			for(int j = 1; j <= g->nvertices; j++)
			{
				if((g->weight[i][k] != MAXINT) && (g->weight[k][j] != MAXINT))
				{
					through_k = g->weight[i][k] + g->weight[k][j];
					if(through_k < g->weight[i][j])
						g->weight[i][j] = through_k;
				}
			}
		}
	}
}

void Graph::floyd(int limit)
{
	int c {0}, through_k {0};

	for(int k = 1; k <= limit; k++)
	{
		for(int i = 1; i <= g->nvertices; i++)
		{
			for(int j = 1; j <= g->nvertices; j++)
			{
				if((g->weight[i][k] != MAXINT) && (g->weight[k][j] != MAXINT))
				{
					through_k = g->weight[i][k] + g->weight[k][j];
					if(through_k < g->weight[i][j])
						g->weight[i][j] = through_k;
				}
			}
		}
	}
}

void Graph::set_nvertices(int n)
{
	g->nvertices = n;
}
