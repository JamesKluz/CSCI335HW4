/****************************************
 File:      TestRandomGraph.cpp
 Author:    James Kluz
 Purpose:   
			
 Date:      4/14/2016
 **************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){
 	if(argc != 2){
 		std::cout << "Usage: " << argv[0] << " <graphSize> " << std::endl;
        return 0;
    }
    const int vertex_number = atoi(argv[1]);

	srand(time(0)); //use current time as seed for random generator
	const int maximum_value = vertex_number;
	while (true) {
 		const int random_variable = rand() % maximum_value + 1;
 		cout << random_variable << endl;
 	// break from loop based on a condition.
 	return 0;
}