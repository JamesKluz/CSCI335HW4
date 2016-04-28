/****************************************
 File:      TestRandomGraph.cpp
 Author:    James Kluz
 Purpose:   Builds a random undirected graph with vertex ids being ints.
            The graph will have N vertices where N is the first command 
            line arguement. We use a union-find structure to simulate
            connections and we add connections until all vertices are 
            connected. The program then prints out some statistics about
            the number of edges in the graph.
 Date:      4/14/2016
 **************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "DisjSets.h"
#include "Graph.h" 

int main(int argc, char **argv){
 	if(argc != 2){
 		std::cout << "Usage: " << argv[0] << " <graphSize> " << std::endl;
        return 0;
    }
    const int vertex_number = atoi(argv[1]);
    Graph<int> testGraph;
    DisjSets<int> vertex_sets;
    for(int k = 1; k <= vertex_number; k++){
    	testGraph.Add_vertex(k);
    	vertex_sets.Add_elem(k);
    }
    int i1, i2;
	srand(time(0)); //use current time as seed for random generator
	int count = 0;
	while (vertex_sets.Get_number_of_sets() > 1) {
 		i1 = rand() % vertex_number + 1;
 		i2 = rand() % (vertex_number-1) + 1;
 		if(i1 == i2)
 			++i2;
 		if(!testGraph.Is_connected(i1, i2)){
 			testGraph.Add_connection(i1, i2, 1.0);
 			testGraph.Add_connection(i2, i1, 1.0);
 		}
 		vertex_sets.Connect_elems(i1, i2);
 		++count;
 	}
 	//std::cout << count <<std::endl;
 	testGraph.Print_stats();
 	return 0;
}