/****************************************
 File:      Vertex.h
 Author:    James Kluz
 Purpose:   
			Template Class for a Vertex in
				a graph.
 Date:      4/14/2016
 **************************************/
 #ifndef 	CSCI_335_VERTEX_H
 #define	CSCI_335_VERTEX_H
 #include <unordered_map>
 #include <iostream>
 #include <list>		//for list
 #include <utility>		//for std::pair

template <typename Object>
class Vertex{
public:
	Vertex(Object this_key){
		key_ = this_key;
	}
	void add_edge(std::pair< Vertex<Object> *, double > edge){
		adjacent_nodes_.push_back(edge);
	}
	Object getkey(){
		return key_;
	}
private:
	//1st position in pair is the key for a vertex
	//2nd position is the weight of the path to the
	//adjacent node
	Object key_;
	std::list<std::pair< Vertex<Object>*, double>> adjacent_nodes_;
};

template <typename Object>
class Graph{
public:
	void add_connection(Object a, Object b, double weight){
		if(vertex_map_.find(a) == vertex_map_.end()){
			vertex_map_[a] = Vertex<Object>{a};
		}
		if(vertex_map_.find(b) == vertex_map_.end()){
			vertex_map_[b] = Vertex<Object>{b};
		}
		Vertex<Object>* temp = & vertex_map_[b];
		std::pair<Vertex<Object>*, double> new_connection = std::make_pair(temp, weight);
		vertex_map_[a].add_edge(new_connection);
	}
private:
	std::unordered_map<Object, Vertex<Object>> vertex_map_;	
};

 #endif