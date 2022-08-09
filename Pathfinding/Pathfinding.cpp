// ============================================================
// Amy Elliott's TOGA C++ Submission - BFS & Graph Theory Study
// ============================================================

#include <iostream>
#include "Pathfinding.h"

// Connects our graph nodes.
void Graph::addEdge(int fromNode, int toNode)
{
	adjacencyList[fromNode].push_back(toNode);
	adjacencyList[toNode].push_back(fromNode);
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