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
 #include <climits>
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
	void Print_shortest_path(Object * graph_node) const{
		if(graph_node->path_prev_ == nullptr){
			std::cout << graph_node->id_ << ", ";
		}
		else{
			Print_shortest_path_internal(graph_node->prev);
			std::cout << graph_node->id_ << ", ";
		}
	}
	bool Is_connected(const Object &v2) const{
		for(auto it = adjacent_nodes_.begin(); it != adjacent_nodes_.end(); ++it){
			if(it->first->id_ == v2){
				return true;
			} 
		}
		return false;
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
	bool Is_connected(const Object &v1, const Object &v2){
		if(vertex_map_.find(v1) == vertex_map_.end() || vertex_map_.find(v2) == vertex_map_.end())
			return false;
		const Vertex<Object> & temp = vertex_map_[v1];
		return temp.Is_connected(v2);
	}
	void Dijkstra(Object start){
 		std::priority_queue<Vertex<Object> *, std::vector<Vertex<Object> *>, CompVertDist<Object>> distance_queue;
		for(auto it = vertex_map_.begin(); it != vertex_map_.end(); ++it ){
			Reset_vertex(it->second);
		}
		vertex_map_[start].distance_ = 0.0;
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
			v->known_ = true;
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

	size_t Get_size(){
		return vertex_map_.size();
	}

	void Print_stats(){
		int smallest_out = INT_MAX;
		int largest_out = 0;
		int edge_total = 0;


		for(auto it = vertex_map_.begin(); it != vertex_map_.end(); ++it){
			int current = it->second.adjacent_nodes_.size();
			edge_total += current;
			if(current < smallest_out)
				smallest_out = current;
			if(largest_out < current)
				largest_out = current;
		}

		std::cout << "The Random graph of size " << vertex_map_.size() << " has " << edge_total << " edges\n";
		std::cout << "The smallest out degree is: " << smallest_out << std::endl;
		std::cout << "The largest out degree is: " << largest_out << std::endl;
		std::cout << "The average out degree is: " << edge_total / static_cast<double>(vertex_map_.size()) << std::endl;
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
	void Reset_vertex(Vertex<Object> v){
		v.distance_ = DBL_MAX;
		v.known_ = false;
		v.path_prev_ = nullptr;
		v.starting_vertex_ = false;
	}
	std::unordered_map<Object, Vertex<Object>> vertex_map_;	
	size_t edge_count_;
};

 #endif