/****************************************
 File:      Graph.h
 Author:    James Kluz
 Purpose:   
			Template Class for a Graph,
			that has Dijkstra as a member function
 Requires:	Graph.cpp
 Date:      4/14/2016
 **************************************/
 #ifndef CSCI_335_GRAPH_H
 #define CSCI_335_GRAPH_H

 #include <unordered_map>
 #include <iostream>
 #include <list>		//for list
 #include <utility>		//for std::pair
 #include <float.h>		//DBL_MAX
 #include <climits>		//INT_MAX
 #include <queue>

template<typename Object>
 class Graph;

template <typename Object>
class Vertex{
public:
	friend class Graph<Object>;
	Vertex() = default;
	Vertex(Object key){
		id_ = key;
		distance_ = DBL_MAX;
		known_ = false;
		path_prev_ = nullptr;
		starting_vertex_ = false;
	}
	//accessor function needed for comparator class
	//no precondition
	//returns a double corresponding to the sum
	//of the edge weights along the shortest path
	//to the starting vertex
	int Get_distance() const {
		return distance_;
	}
private:
	Object id_;
	double distance_;
	bool known_;
	Vertex<Object> * path_prev_;
	bool starting_vertex_;
	std::list<std::pair< Vertex<Object>*, double>> adjacent_nodes_;
};

//Comparator class that orders vertices by
//their distance to the starting node
template <typename Object>
class CompVertDist{
 public:
 	bool operator()(const Vertex<Object> *lhs, const Vertex<Object> * rhs) const{
 		//DEFINED THIS WAY TO MAKE PRIORITY_QUEUE A MIN HEAP
 		return lhs->Get_distance() > rhs->Get_distance(); 
 	}
};

template <typename Object>
class Graph{
public:
	Graph() = default;
	~Graph() = default;

	Graph(const Graph & rhs) = delete;
	Graph(Graph && rhs) = delete;
	Graph & operator=(const Graph & rhs) = delete;
	Graph & operator=(Graph && rhs) = delete; 
	//Adds a vertex to the graph with ID = a.
	//If a is already an ID then nothing will happen
	//returns true if vertex 'a' succesfully added
	bool Add_vertex(Object a);
	//Adds a directed edge from vertex with id 'a' to
	//vertex of id 'b' with weight "weight".
	//If there already exists an edge from a to b, this
	//will add another edge. 
	//If either 'a' or 'b' are not in the graph, they are added. 
	void Add_connection(Object a, Object b, double weight);
	//Returns a double corresponding to the weight of the 
	//edge connecting a to b. If no edge exists, then the 
	//function returns DBL_MAX
	double Edge_weight(const Object &a, const Object &b) const;
	//returns true if there exists an edge from v1 to v2
	//otherwise returns false
	bool Is_connected(const Object &v1, const Object &v2);
	//Expects there to be no cycles in the graph
	//Finds the shortest path from 'start' to all other vertices
	//afterwords, each vertex has it's distance_ set to shortest
	//path distance if it exists and DBL_MAX otherwise.
	//path_prev_ is a pointer pointing to prevous vertex in shortest path
	void Dijkstra(Object start);
	//Prints the shortest path from the starting vertex to graph_node
	//if dijkstra has not been run yet then distances
	//will print out as infinity 
	void Print_shortest_path(const Object & graph_node) const;
	//returns true if vertex_node is an id of a vertex in the graph
	//returns false otherwise
	bool Contains(const Object & vertex_node) const;
	//Returns the size_t corresponding to the number of vertices in the graph
	size_t Get_size() const;
	//Function for CSCI_335 HW 4, outputs the following:
	//The Random graph of size N has M edges
	//The smallest out degree is: ?
	//The largest out degree is: ?
	//The average out degree is: ?
	void Print_stats() const;
private:
	//recursive function for printing the shortest path
	//called by Print_shortest_path(const Object & graph_node)
	//Prints id of current node and then calls itself on
	//node pointed to by path_prev_ stored in vertex
	void Print_shortest_path_internal(const Vertex<Object> * graph_node) const;
	//sets distance_ = DBL_MAX  /  known_ = false  /  path_prev_ = nullptr
	//and   starting_vertex_ = false  
	void Reset_vertex(Vertex<Object> v);
	std::unordered_map<Object, Vertex<Object>> vertex_map_;	
	size_t edge_count_;
};

#include "Graph.cpp"
#endif