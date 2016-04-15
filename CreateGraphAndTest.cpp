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

 int main(int argc, char **argv){
 	if(argc != 3){
 		std::cout << "Usage: " << argv[0] << " <graphInputFilename> <queryfilename> " << std::endl;
        return 0;
    }

    const std::string words_filename(argv[1]);
    const std::string query_filename(argv[2]);

    Graph<int> testgraph;
    testgraph.add_connection(1, 2, 2.7);	

    return 0;
 }