/****************************************
 File:      DisjSets.h.h
 Author:    James Kluz
 Purpose:   
			Template Class for dynamic
			connectivity of sets.
 Date:      4/14/2016
 **************************************/
 #ifndef 	CSCI_335_DISJSETS_H
 #define	CSCI_335_DISJSETS_H

 #include <unordered_map>

template <typename Object>
class DisjSets{
public:
	DisjSets(){
		number_of_sets_ = 0;
	}
	void Add_elem(Object elem){
		if(sets_.find(elem) == sets_.end()){
			sets_[elem] = elem;
			set_heights_[elem] = 0;
			++number_of_sets_;
		}		
	}
		Object Find_root(Object elem){
		if(sets_[elem] == elem)
			return elem;
		else
			return sets_[elem] = Find_root(sets_[elem]);
	}
	void Connect_elems(Object elem1, Object elem2){
		Add_elem(elem1);
		Add_elem(elem2);
		root1 = Find_root(elem1);
		root2 = Find_root(elem1);
		if(root1 == root2)
			return;
		Union_sets(root1, root2);
		--number_of_sets_;
	}
	int Get_number_of_sets(){
		return number_of_sets_;
	}


private:
	void Union_sets(Object root1, Object root2){
		if(set_heights_[root1] < set_heights_[root2]){
			sets_[root1] = root2;
		} else if(set_heights_[root2] < set_heights_[root1]){
			sets_[root2] = root1;
		} else{
			sets_[root2] = root1;
			set_heights_[root1] += 1; 
		}
	}
	std::unordered_map<Object, Object> sets_;
	std::unordered_map<Object, int> set_heights_;
	int number_of_sets_;	
 }; 


 #endif