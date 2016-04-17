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
 #include <float.h>		//DBL_MAX
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
	void Add_edge(std::pair< Vertex<Object> *, double > edge){
		adjacent_nodes_.push_back(edge);
	}
	Object Get_id(){
		return id_;
	}
	double Get_edge_weight(Object b){
		auto x = adjacent_nodes_.begin();
		while(x != adjacent_nodes_.end()){
			if(x->first->Get_id() == b)
				return x->second;
			x++;
		} 
		return DBL_MAX;
	}
	void Reset(){
		distance_ = DBL_MAX;
		known_ = false;
		path_prev_ = nullptr;
		starting_vertex_ = false;
	}
	void Set_distance(double dist_new){
		distance_ = dist_new;
	}
	double Get_distance() const {
		return distance_;
	}
	void Set_known(bool truth_value){
		known_ = truth_value;
	}
	void Print_shortest_path(Object * graph_node) const{
		if(graph_node->path_prev_ == nullptr){
			std::cout << graph_node->id_ << ", ";
		}
		else{
			Print_shortest_path_internal(graph_node->prev);
			std::cout << graph_node->id_ << ", ";
		}
	}

private:
	void Print_shortest_path_internal(Object * graph_node) const{
		if(graph_node->path_prev_ == nullptr){
			std::cout << graph_node->id_ << ", ";
		}
		else{
			Print_shortest_path_internal(graph_node->prev);
			std::cout << graph_node->id_ << ", ";
		}
	}
	Object id_;
	double distance_;
	bool known_;
	Vertex<Object> * path_prev_;
	bool starting_vertex_;
	//1st position in pair is the key for a vertex
	//2nd position is the weight of the path to the
	//adjacent node
	std::list<std::pair< Vertex<Object>*, double>> adjacent_nodes_;
};

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
	void Add_vertex(Object a){
		if(vertex_map_.find(a) == vertex_map_.end()){
			vertex_map_[a] = Vertex<Object>(a);
		}
	}
	void Add_connection(Object a, Object b, double weight){
		if(vertex_map_.find(a) == vertex_map_.end()){
			vertex_map_[a] = Vertex<Object>(a);
		}
		if(vertex_map_.find(b) == vertex_map_.end()){
			vertex_map_[b] = Vertex<Object>(b);
		}
		Vertex<Object>* temp = & vertex_map_[b];
		std::pair<Vertex<Object>*, double> new_connection = std::make_pair(temp, weight);
		vertex_map_[a].Add_edge(new_connection);
	}
	double Edge_weight(Object a, Object b){
		auto x = vertex_map_.find(a);
		if(x != vertex_map_.end()){
			return x->second.Get_edge_weight(b);
		}
		else
			return DBL_MAX;
	}
	void Dijkstra(Object start){
 		std::priority_queue<Vertex<Object> *, std::vector<Vertex<Object> *>, CompVertDist<Object>> distance_queue;
		for(auto it = vertex_map_.begin(); it != vertex_map_.end(); ++it ){
			it->second.Reset();
		}
		vertex_map_[start].Set_distance(0.0);
		Vertex<Object> *v = & vertex_map_[start];
		v->starting_vertex_ = true;
		distance_queue.push(v);
		while(true){
			bool success = false;
			while(!distance_queue.empty() && !success){
				v = distance_queue.top();
				distance_queue.pop();
				if(!v->known_)
					success = true;
			}
			if(!success)
				break;
			v->Set_known(true);
			//THIS LOOP IS WHY I MADE GRAPH A FRIEND OF 
			for(auto it = v->adjacent_nodes_.begin(); it != v->adjacent_nodes_.end(); ++it){
				if(v->distance_ + it->second < it->first->distance_){
					it->first->distance_ = v->distance_ + it->second;
					it->first->path_prev_ = v;
					distance_queue.push(it->first);
				}
			}
		}
	}	
	//ANOTHER FUNCTION THAT EXPECTS TO BE VERTEX TO BE FRIEND
	void Print_shortest_path(const Object & graph_node) {
		if(vertex_map_.find(graph_node) == vertex_map_.end()){
			std::cout << "Vertex " << graph_node << " does not exist!\n";
			return;
		}
		std::cout << graph_node << ": ";
		Vertex<Object> * temp = & vertex_map_[graph_node];
		if(temp->starting_vertex_){
			std::cout << temp->id_ << " is the starting point, Total Cost: 0.0\n";
			return;
		}
		Print_shortest_path_internal(temp);
		std::cout << "Total Cost: " << temp->distance_ << std::endl;
	}

	bool Contains(Object vertex_node){
		return vertex_map_.find(vertex_node) != vertex_map_.end();
	}

private:
	//ANOTHER FUNCTION THAT EXPECTS TO BE VERTEX TO BE FRIEND
	void Print_shortest_path_internal(Vertex<Object> * & graph_node) const{
		if(graph_node->path_prev_ == nullptr){
			std::cout << graph_node->id_ << ", ";
		}
		else{
			Print_shortest_path_internal(graph_node->path_prev_);
			std::cout << graph_node->id_ << ", ";
		}
	}
	std::unordered_map<Object, Vertex<Object>> vertex_map_;	
};

 #endif