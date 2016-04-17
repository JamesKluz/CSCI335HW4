/****************************************
 File:      Graph.h
 Author:    James Kluz
 Purpose:   
			Template Class for a Vertex in
				a graph.
 Date:      4/14/2016
 **************************************/
 #ifndef 	CSCI_335_GRAPH_H
 #define	CSCI_335_GRAPH_H
 #include <unordered_map>
 #include <iostream>
 #include <list>		//for list
 #include <utility>		//for std::pair
 #include <float.h>		//DBL_MAX
 #include <queue>



template <typename Object>
class Graph{
public:
	void add_vertex(Object a){
		if(vertex_map_.find(a) == vertex_map_.end()){
			vertex_map_[a] = Vertex(a);
		}
	}
	void add_connection(Object a, Object b, double weight){
		if(vertex_map_.find(a) == vertex_map_.end()){
			vertex_map_[a] = Vertex(a);
		}
		if(vertex_map_.find(b) == vertex_map_.end()){
			vertex_map_[b] = Vertex(b);
		}
		Vertex* temp = & vertex_map_[b];
		std::pair<Vertex*, double> new_connection = std::make_pair(temp, weight);
		vertex_map_[a].adjacent_nodes_.push_back(new_connection);
	}
	double edge_weight(Object a, Object b){
		auto x = vertex_map_.find(a);
		if(x != vertex_map_.end()){
			return x->second.get_edge_weight(b);
		}
		else
			return DBL_MAX;
	}
	void Dijkstra(Object start){
 		std::priority_queue<Vertex, std::vector<Vertex>, CompVertDist> distance_queue;
		for(auto it = vertex_map_.begin(); it != vertex_map_.end(); ++it ){
			it->second.distance_ = DBL_MAX;
			it->second.known_ = false;
		}
		vertex_map_[start].distance_ = 0.0;
		Vertex v = vertex_map_[start];
		distance_queue.push(v);
		while(true){
			if(distance_queue.empty())
				break;
			v = distance_queue.top();
			distance_queue.pop();
			v.known_ = true;
			for(auto it = v.adjacent_nodes_.begin(); it != v.adjacent_nodes_.end(); ++it){
				if(v.distance_ + it->second < it->first->distance_){
					it->first->distance_ = v.distance_ + it->second;
					distance_queue.push(it->first);
				}
			}
		}
	}	

private:
	struct Vertex{
		Vertex() = default;

		Vertex(Object key){
			id_ = key;
			distance_ = DBL_MAX;
			known_ = false;
		}
		double get_edge_weight(Object b){
			auto x = adjacent_nodes_.begin();
			while(x != adjacent_nodes_.end()){
				if(x->first->id_ == b)
					return x->second;
				x++;
			} 
			return DBL_MAX;
		}
		Object id_;
		double distance_;
		bool known_;
		Object
		std::list<std::pair< Vertex*, double>> adjacent_nodes_;
	};
	std::unordered_map<Object, Vertex> vertex_map_;	

	class CompVertDist{
 	public:
 		bool operator()(const Vertex & lhs, const Vertex & rhs) const{
 			//DEFINED THIS WAY TO MAKE PRIORITY_QUEUE A MIN HEAP
 			return lhs.distance_ > rhs.distance_; 
 		}
	};
};

 #endif