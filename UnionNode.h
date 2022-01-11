//
// Created by harel on 1/8/2022.
//

#ifndef NEW_TREE_AVL_UNIONNODE_H
#define NEW_TREE_AVL_UNIONNODE_H

template <class T>
class UnionNode {
	int size;
	int id;
	T* value;
	UnionNode<T>* parent;
public:
	UnionNode():size(1),id(0), value(new T(id)), parent(nullptr) {}

	~UnionNode(){
		delete value;
	}
	//explicit UnionNode(T* value):size(1),value(value), parent(nullptr) {}

	int get_size()
	{
		return size;
	}
	void increase_size(int amount_to_increase)
	{
		size = size + amount_to_increase;
	}
	void decrease_size(int amount_to_decrease)
	{
		size = size - amount_to_decrease;
	}
	T* get_value()
	{
		return value;
	}
	void set_value(T* new_value)
	{
		value = new_value;
	}
	UnionNode<T>* get_parent()
	{
		return parent;
	}
	void set_parent(UnionNode<T>* new_parent)
	{
		parent = new_parent;
	}
	void set_id(int new_id){
		this->id = new_id;
	}
};


#endif //NEW_TREE_AVL_UNIONNODE_H
