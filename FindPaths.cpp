/****************************************
 File:      FindPaths.cpp
 Author:    James Kluz
 Purpose:   
			Parse and create graph using adjecency list from .txt where each vertex	
			is represented by an integer from 1 to N. Each line	is of the form:
			<vertex> <connected	vertex 1> <weight1>	<connected vertex 2> <weight 2>...
            Then from the command line input, return the shortest path to each vertex
            from the vertex entered on command line along with weight of shortest path
            We do this using Dijkstra.
 Date:      4/14/2016
 **************************************/
#include <iostream>
#include "Graph.h"
#include <fstream>
#include <sstream> 
#include <cstdlib>

//Opens and parses files Graph1.txt and Graph2.txt
//and fills graph with the corresponding vertices and edges
template <typename Object>
void Make_Graph(std::string const & graph_file, Graph<Object> & graph){
    std::ifstream input;
    input.open(graph_file);
    if(input.fail()){
        std::cout << "Failed to open " << graph_file << std::endl;
        exit(1);
    }
    std::string line;
    Object this_vertex;
    Object a_new_vertex;
    double a_new_weight;
    //Kill first line in .txt that specifies the number of vertices
    std::getline(input, line);
    while(std::getline(input, line)){
        if(!line.empty()){
            std::stringstream ss(line);
            ss >> this_vertex;
            graph.Add_vertex(this_vertex);
            while(ss >> a_new_vertex && ss >> a_new_weight){
                graph.Add_connection(this_vertex, a_new_vertex, a_new_weight);
            }
        } 
    }
    input.close();
 }

 int main(int argc, char **argv){
 	if(argc != 3){
 		std::cout << "Usage: " << argv[0] << " <graphInputFilename> <Vertex> " << std::endl;
        return 0;
    }
    const std::string graph_filename(argv[1]);
    const int vertex = atoi(argv[2]);
    Graph<int> testgraph;
    Make_Graph<int>(graph_filename, testgraph);	
    testgraph.Dijkstra(vertex);
    int count = 1;
    while(testgraph.Contains(count)){
        testgraph.Print_shortest_path(count);
        ++count;
    }
    return 0;
 }