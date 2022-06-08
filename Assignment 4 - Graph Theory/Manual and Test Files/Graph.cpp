#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here, and pass the 
// flag to it too.
//
Graph::Graph(string filename, bool flag)
{
	// TODO
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
// The flag determines whether the edges will be added according to a
// directed or undirected graph.
//
void Graph::addEdge(char start, char end, int weight, bool flag)
{
	// TODO
	return;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in the manual.
//
string Graph::display()
{
	// TODO
	return "";
}

// Returns whether the destination city is reachable from the
// origin city or not.
//
bool Graph::Reachable(char start, char end)
{
	// TODO
	return false;
}

//
// Returns the weight of shortest path between origin and destination cities.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	// TODO
	return 0;
}

//
// Implement topological sort on the graph and return the string of the sorted cities
//
string Graph::topoSort()
{
	//TODO
	return "";
}

#endif
