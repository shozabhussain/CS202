#ifndef GRAPH__CPP
#define GRAPH__CPP
#include <string>
#include "Graph.h"
#include<queue>

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here, and pass the
// flag to it too.
//
Graph::Graph(string filename, bool flag)
{
	string myText ;
	ifstream MyReadFile(filename) ;

	while (getline (MyReadFile, myText))
	{
		if (myText[0] == 'n' )
		{
			this -> size = myText[2] - '0' ;

			for(int i=0; i< size; i++)
			{
				vector<shared_ptr<Edge>> vectorTemp ;
				graph.push_back(vectorTemp) ;
			}

			for(int i=0; i< size; i++)
			{
				for(int j=0; j< size; j++)
				{
					shared_ptr<Edge> temp = make_shared<Edge>() ;
					graph[i].push_back(temp) ;
				}
			}
		}
		else if(myText[0] != 'n' && myText[0] != 'c' )
		{
			this -> addEdge( (myText[0]), (myText[2]), (myText[4]-'0'), flag) ;
		}
	}
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
// The flag determines whether the edges will be added according to a
// directed or undirected graph.
//
void Graph::addEdge(char start, char end, int weight, bool flag)
{
	graph[start- 65][end- 65] -> origin = start ;
	graph[start- 65][end- 65] -> dest = end ;
	graph[start- 65][end- 65] -> weight = weight ;

	if(flag == false )
	{
		graph[end- 65][start- 65] ->origin = end ;
		graph[end- 65][start- 65] -> dest = start ;
		graph[end- 65][start- 65] -> weight = weight ;
	}
	return;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in the manual.
//
string Graph::display()
{
	string graphString = "" ;

	for(int i=0; i<size; i++)
	{
		bool inserted = false ;

		for(int j=0; j<size; j++)
		{
			if(graph[i][j] ->origin != '0' && graph[i][j] ->dest != '0' )
			{

				graphString = graphString + "(" + this ->graph[i][j]->origin + "," + this ->graph[i][j]->dest + "," + to_string(this ->graph[i][j]->weight) + ") " ;
				inserted = true ;
			}
		}

		if(inserted == true)
		{
			graphString = graphString + "\n" ;
		}
	}
	return graphString;
}

// Returns whether the destination city is reachable from the
// origin city or not.
//
bool Graph::Reachable(char start, char end)
{
	vector<int> vect ;
	return ReachableHelper(start, end, vect) ;
}

//
// Returns the weight of shortest path between origin and destination cities.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	if(Reachable(start, dest) == false )
	{
		return -1 ;
	}

	vector<int> distanceVector(size, 9999) ;

	distanceVector[start-65] = 0 ;

	priority_queue<shared_ptr<Edge>> frontier ;
	vector<int> cloud(size, 0) ;

	shared_ptr<Edge> temp = make_shared<Edge>(start, start, 0) ;
	frontier.push(temp) ;

	while( !frontier.empty() )
	{
		shared_ptr<Edge> min ;
		min = frontier.top()  ;
		frontier.pop() ;

		int minVertice = (min ->dest) - 65 ;

		for(int i=0; i<size; i++)
		{
			if( distanceVector[minVertice] + graph[minVertice][i] ->weight < distanceVector[i] && graph[minVertice][i] ->weight != 0)
			{
				distanceVector[i] = distanceVector[minVertice] + graph[minVertice][i] ->weight ;

				shared_ptr<Edge> temp = make_shared<Edge>(char(minVertice+65), char(i+65), distanceVector[i]) ;
				frontier.push(temp) ;
			}
		}
	}

	return distanceVector[dest-65] ;
}

//
// Implement topological sort on the graph and return the string of the sorted cities
//
string Graph::topoSort()
{
	string sortedPath = "";

	vector<int> explored(size, 0) ;

	while(1)
	{
		vector<int> inDegree(size, 0) ;

		for(int i=0; i<size; i++)
		{
			if(explored[i] == 0)
			{
				for(int j=0; j<size; j++)
				{
					if(graph[j][i] ->weight !=0 )
					{
						if(explored[j] == 0)
						{
							inDegree[i] = inDegree[i] + 1 ;
						}

					}
				}
			}
		}

		int minInDegreeIndex = 9999 ;
		int minIndegree = 9999 ;

		for(int i=0; i<size; i++)
		{
			if(inDegree[i] < minIndegree && explored[i] == 0)
			{
				minIndegree = inDegree[i] ;
				minInDegreeIndex = i ;
			}
		}

		sortedPath = sortedPath + char(minInDegreeIndex+65) ;
		explored[minInDegreeIndex] = 1 ;

		if(sortedPath.length() == size)
		{
			return sortedPath ;
		}
	}
}

bool Graph::ReachableHelper(char start, char end, vector<int> &vect)
{
	int startIndex = start - 65 ;
	int endIndex = end - 65 ;

	if(graph[startIndex][endIndex] ->weight != 0)
	{
		return true ;
	}
	else
	{
		for(int i=0; i<size; i++)
		{
			bool explored = false ;

			for(int j=0; j<vect.size(); j++)
			{
				if(i == vect[j])
				{
					explored = true ;
				}
			}

			if(graph[startIndex][i] -> weight != 0 && explored == false)
			{
				vect.push_back(i) ;

				if( ReachableHelper(i+65, end, vect) == true )
				{
					return true ;
				}
			}
		}
	}

	return false ;
}

#endif
