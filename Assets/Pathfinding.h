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
	void Dijkstras_Algorithm(int graph[6][6]);
	void Dijkstras_Algorithm_SP(int graph[6][6], int start, int end);
};