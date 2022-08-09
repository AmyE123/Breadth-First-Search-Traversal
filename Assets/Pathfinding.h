// ============================================================
// Amy Elliott's TOGA C++ Submission - BFS & Graph Theory Study
// ============================================================

#include <iostream>
#include <list>
#include <queue>
#include <fstream>
#include "string"

#pragma once

using namespace std;

class Graph
{
	int vertex;
	list<int>* adjacencyList;

public:
	Graph(int v)
	{
		this->vertex = v;
		adjacencyList = new list<int>[v];
	}


	void addEdge(int fromNode, int toNode);
	void BFS(Graph g, int root, int dest);
};