#include <iostream>
#include "Pathfinding.h"

//TODO: Refine comments, and remove unneeded comments
//TODO: Change all variable and function names to fit C++ code conventions and/or make them easier to understand

#define INT_MAX 1000	//just a max cap

// Connects our graph nodes.
void Graph::addEdge(int fromNode, int toNode)
{
	adjacencyList[fromNode].push_back(toNode);
	adjacencyList[toNode].push_back(fromNode);
}

int selectMinVertex(vector<int>& value, vector<bool>& processed)
{
	int minimum = INT_MAX;
	int vertex;
	for (int i = 0; i < 6; ++i)
	{
		if (processed[i] == false && value[i] < minimum)
		{
			vertex = i;
			minimum = value[i];
		}
	}
	return vertex;
}

int selectMinVertex2(vector<int>& value, vector<bool>& processed, int start, int end)
{
	int minimum = INT_MAX;
	int vertex;
	for (int i = 0; i < end; ++i)
	{
		if (processed[i] == false && value[i] < minimum)
		{
			vertex = i;
			minimum = value[i];
		}
	}
	return vertex;
}


// Performs Dijkstra's algorithm on our graph
void Dijkstras_Algorithm(int graph[6][6])
{
	int parent[6];	//stores the shortest path
	vector<int> value(6, INT_MAX);
	vector<bool> processed(6, false);	//if true, the vertex has been processed

	parent[0] = -1;	//start node has no parent
	value[0] = 0;

	for (int i = 0; i < 6 - 1; ++i)
	{
		int U = selectMinVertex(value, processed);
		processed[U] = true;

		for (int j = 0; j < 6; j++)
		{
			if (graph[U][j] != 0 && processed[j] == false && value[U] != INT_MAX && (value[U] + graph[U][j] < value[j]))
			{
				value[j] = value[U] + graph[U][j];
				parent[j] = U;
			}
		}
	}
	for (int i = 1; i < 6; ++i)
	{
		cout << "U -> V // " << parent[i] << " (TOP) -> " << i << " (SIDE) // weight = " << graph[parent[i]][i] << "\n";
	}
}

// Performs Dijkstra's algorithm on our graph & gives shortest path
void Dijkstras_Algorithm_SP(int graph[6][6], int start, int end)
{
	int parent[6];	//stores the shortest path
	int parent2[6];
	vector<int> value(6, INT_MAX);
	vector<bool> processed(6, false);	//if true, the vertex has been processed

	parent[0] = -1;	//start node has no parent
	value[0] = 0;

	for (int i = 0; i < 6 - 1; ++i)
	{
		int U = selectMinVertex(value, processed);
		processed[U] = true;

		for (int j = 0; j < 6; j++)
		{
			if (graph[U][j] != 0 && processed[j] == false && value[U] != INT_MAX && (value[U] + graph[U][j] < value[j]))
			{
				value[j] = value[U] + graph[U][j];
				parent[j] = U;
				cout << parent[j] + 1 << " to " << j + 1 << " weight = " << graph[parent[j]][j] << "\n";
			}
		}
	}
	for (int i = 1; i < 6; ++i)
	{
		if (parent[i] == start || end)
		{
			parent2[i] = parent[i];
		}
	}

	for (int i = 1; i < end + 1; ++i)
	{
		//cout << "U -> V // " << parent2[i] + 1 << " (TOP) -> " << i + 1 << " (SIDE) // weight = " << graph[parent2[i]][i] << "\n";
		cout << parent2[i] + 1 << " to " << i + 1 << " weight = " << graph[parent[i]][i] << "\n";
	}
}

// Performs a Breadth First Search Traversal on our graph.
void Graph::BFS(Graph g, int root, int dest)
{
	bool* nodeIsVisited = new bool[vertex];
	list<int> queue;
	nodeIsVisited[root] = true;
	queue.push_back(root);

	// Checking if our inputted values are valid.
	if (root >= 27 || dest >= 27 || root < 0 || dest < 0)
 	{
		cout << "Invalid path." << endl;
		return;
	}

	// Setting all the booleans for each node to not visited
	for (int i = 0; i < vertex; i++)
	{
		nodeIsVisited[i] = false;
	}

	// While our queue isn't empty, iterate though all the edges of our current node and set it to visited
	while (!queue.empty())
	{
		int v = queue.front();
		cout << v << endl;
		queue.pop_front();

		if (v == dest)
		{
			cout << "Got to destination: " << v << " = " << dest << endl;
			return;
		}	

		for (list<int>::iterator it = adjacencyList[v].begin(); it != adjacencyList[v].end(); it++)
		{
			int vertex = *it;

			if (!nodeIsVisited[vertex])
			{
				nodeIsVisited[vertex] = true;
				queue.push_back(vertex);
			}
		}
	}
}

int textLineCount()
{
	string txt;
	int lines = 0;
	ifstream input;
	input.open("adjList.txt");

	while (!input.eof())
	{
		getline(input, txt);
		lines++;
	}
	return lines;
}

// Adds all of the edges onto our graph from our adjList.txt file
void adjacentListGraph(Graph g)
{
	ifstream file("adjList.txt");
	vector<int> roots;
	vector<int> destinations;

	int r, d;
	while (file >> r >> d)
	{
		roots.push_back(r);
		destinations.push_back(d);
	}

	for (int i = 0; i < roots.size(); i++)
	{
		g.addEdge(roots[i], destinations[i]);
	}
}

int main()
{
	//TODO: Clean up user interface
	//TODO: Allow user to pick method

	//adjacency matrix definition
	int graphMatrix[6][6] = { {0, 5, 1, 2, 0, 0}, {5, 0, 3, 0, 2, 0}, {1, 3, 0, 4, 0, 0}, {2, 0, 4, 0, 6, 5}, {0, 2, 0, 6, 0, 7}, {0, 0, 0, 5, 7, 0} };

	int x;

	cout << "Select 0 for Dijkstra's Algorithm, or 1 for Breadth First Search" << "\n";
	cin >> x;

	if (x == 0)
	{
		int rootPoint;
		int destinationPoint;

		cout << "Enter a root point: ";
		cin >> rootPoint;

		cout << "Enter a destination point: ";
		cin >> destinationPoint;

		//Dijkstras_Algorithm(graphMatrix);
		Dijkstras_Algorithm_SP(graphMatrix, rootPoint, destinationPoint);
		return 0;
	}
	else
	{
		Graph g(textLineCount());

		adjacentListGraph(g);

		int rootPoint;
		int destinationPoint;

		cout << "Enter a root point: ";
		cin >> rootPoint;

		cout << "Enter a destination point: ";
		cin >> destinationPoint;

		g.BFS(g, rootPoint, destinationPoint);
	}

}