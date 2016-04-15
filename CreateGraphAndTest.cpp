/****************************************
 File:      CreateGraphAndTest.cpp
 Author:    James Kluz
 Purpose:   
			Parse and create graph using adjecency list from Graph1.txt where each vertex	
			is represented by an integer from 1 to N. Each line	is of the form:
			<vertex> <connected	vertex 1> <weight1>	<connected vertex 2> <weight 2>...
			Then take in a series of quesries from a second text file where the queries
			are of the form:
			n m \n --> we check to see if n is connected to m and then output the weight.
 Date:      4/14/2016
 **************************************/
#include <iostream>
#include "Vertex.h"
#include <fstream>
#include <sstream> 

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
    while(std::getline(input, line)){
        if(!line.empty()){
            std::stringstream ss(line);
            ss >> this_vertex;
            graph.add_vertex(this_vertex);
            while(ss >> a_new_vertex && ss >> a_new_weight){
                graph.add_connection(this_vertex, a_new_vertex, a_new_weight);
            }
        } 
    }
    input.close();
 }

template <typename Object>
void Query_Graph(std::string const & querry_file, Graph<Object> & graph){
    std::ifstream input;
    input.open(querry_file);
    if(input.fail()){
        std::cout << "Failed to open " << querry_file << std::endl;
        exit(1);
    }
    std::string line;
    Object a;
    Object b;
    double edge_w;
    while(std::getline(input, line)){
        if(!line.empty()){
            std::stringstream ss(line);
            ss >> a;
            ss >> b;
            edge_w = graph.edge_weight(a, b);
            if(edge_w == DBL_MAX){
                std::cout << a << " " << b << ": Not Connected\n";
            }
            else{
                std::cout << a << " " << b << ": Connected, edge weight is " << edge_w << std::endl;
            }
        }
    }
    input.close();
} 

 int main(int argc, char **argv){
 	if(argc != 3){
 		std::cout << "Usage: " << argv[0] << " <graphInputFilename> <queryfilename> " << std::endl;
        return 0;
    }

    const std::string graph_filename(argv[1]);
    const std::string query_filename(argv[2]);

    Graph<int> testgraph;
    Make_Graph<int>(graph_filename, testgraph);	
    Query_Graph<int>(query_filename, testgraph);

    return 0;
 }