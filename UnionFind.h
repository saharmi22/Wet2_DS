//
// Created by harel on 1/8/2022.
//

#ifndef NEW_TREE_AVL_UNIONFIND_H
#define NEW_TREE_AVL_UNIONFIND_H
#include "UnionNode.h"

template <class T>
class UnionFind {
	int size;
	UnionNode<T>** union_arr;
public:
	explicit UnionFind(int size):size(size), union_arr(new UnionNode<T>*[size]) {
		for (int i = 0; i < size; ++i) {
			union_arr[i] = new UnionNode<T>(i);
			union_arr[i]->set_id(i);
		}
	}
	~UnionFind()
	{
		for (int i = 0; i < size; ++i) {
			delete union_arr[i];
		}
		delete[] union_arr;
	}

	UnionNode<T>* get_group(UnionNode<T>* input){
		UnionNode<T>* current = input;
		UnionNode<T>* parent = current->get_parent();
		while(parent){
			current = parent;
			parent = current->get_parent();
		}
		return current;
	}

	T* get_union(int cell){
		UnionNode<T>* cell_union = get_group(union_arr[cell]);
		UnionNode<T>* temp = union_arr[cell];
		UnionNode<T>* temp_parent = temp->get_parent();
		if(temp_parent) {
			while (temp_parent->get_parent()) {

				temp->set_parent(cell_union);
				temp_parent->decrease_size(temp->get_size());
				temp = temp_parent;
				temp_parent = temp->get_parent();
			}
		}
		return cell_union->get_value();
	}

	void to_union(int a, int b)
	{
		UnionNode<T>* union_a = get_group(union_arr[a]);
		UnionNode<T>* union_b = get_group(union_arr[b]);
		if(union_a->get_size()>union_b->get_size()){
			union_b->set_parent(union_a);
			union_a->increase_size(union_b->get_size());
		}
		else{
			union_a->set_parent(union_b);
			union_b->increase_size(union_a->get_size());
		}
	}
};


#endif //NEW_TREE_AVL_UNIONFIND_H
