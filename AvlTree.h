//
// Created by harel on 1/3/2022.
//

#ifndef NEW_TREE_AVL_NEW_AVL_TREE_H
#define NEW_TREE_AVL_NEW_AVL_TREE_H
//
// Created by harel on 11/27/2021.
//

enum tree_result{ALREADY_EXIST,TREE_SUCCESS,MEMORY_PROBLEM};

template <class Value, class Key>
class AVLtree{
private:
	Value* tree_value;
	Key* tree_key;
	int tree_bf;
	int tree_height;
	int tree_size;
	int tree_extra_content;
	AVLtree<Value, Key>* tree_left;
	AVLtree<Value, Key>* tree_right;
	AVLtree<Value, Key>* dad;

	void increase_extra(int to_increase){
		this->tree_extra_content += to_increase;
	}
	int get_extra(){
		return tree_extra_content;
	}
	void set_extra(int ex){
		this->tree_extra_content = ex;
	}
	Key* get_key(){
		return tree_key;
	}
	void set_key(Key* new_key){
		this->tree_key = new_key;
	}

	void fix_heights(){
		int left_height = ((!this->get_left()) ? 0 : (this->get_left_tree_height() ));
		int right_height = ((!this->get_right()) ? 0 : (this->get_right_tree_height()));
		this->tree_height = 1 + ((left_height > right_height) ? left_height : right_height);
		this->tree_bf = left_height - right_height;
		this->tree_size = 1 + ((this->get_right()) ? (this->get_right())->getsize() : 0) + ((this->get_left()) ? (this->get_left())->getsize() : 0);
		if(this->get_right() && this->get_left()) {
			this->set_extra(*(this->get_key()) + (this->get_right()->get_extra()) + (this->get_left()->get_extra()));
		}
		else if(this->get_right()) {
			this->set_extra(*(this->get_key()) + (this->get_right()->get_extra()));
		}
		else if(this->get_left()) {
			this->set_extra(*(this->get_key()) + (this->get_left()->get_extra()));
		}
		else{
			this->set_extra(*(this->get_key()));
		}
		
	}         //for the given tree it updates its height and bf //freed

	void flip_right(bool flipped = false){        //false will roll right and true will roll left
		AVLtree<Value,Key> *Br = this->get_right(flipped);
		AVLtree<Value,Key> *A = this->get_left(flipped);
		Value* b_info = this->tree_value;
		Key* b_key = this->get_key();
		this->set_left(A->get_left(flipped), flipped);
		this->get_left(flipped)->setdad(this);
		this->tree_value = A->tree_value;
		this->set_key(A->get_key());
		A->set_left(A->get_right(flipped), flipped);
		A->set_right(Br, flipped);
		A->get_right(flipped)->setdad(A);
		this->set_right(A, flipped);
		A->set_info(b_info);
		A->set_key(b_key);
		(this->get_right(flipped))->fix_heights();
		this->fix_heights();
	} //freed

	void set_info(Value* info){
		tree_value = info;
	}   //replaces the value of the tree //freed

	int get_right_tree_height(bool flipped = false){
		if(flipped)
			return (this->get_left(flipped))->tree_height;
		return (this->get_right(flipped))->tree_height;
	}       //freed

	int get_left_tree_height(bool flipped = false){
		if(flipped)
			return (this->get_right(flipped))->tree_height;
		return (this->get_left(flipped))->tree_height;
	}      //done //freed

	void set_left(AVLtree<Value, Key>* new_tree, bool flipped = false){
		if(!flipped)
			tree_left = (new_tree);
		else
			tree_right = new_tree;
	}     //done and shared //freed

	void set_right(AVLtree<Value, Key>* new_tree, bool flipped = false){
		if(flipped)
			tree_left = new_tree;
		else
			tree_right= new_tree;
	}   //done and shared //freed
	AVLtree<Value, Key>* getdad(){          // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		return dad;
	}
	void setdad(AVLtree<Value, Key>* father){
		if(this)
		{
			dad= father;
		}
	}

public:

	AVLtree(): tree_value(nullptr),tree_key(nullptr), tree_bf(0) , tree_height(1), tree_size(1), tree_extra_content(0),tree_left(
			nullptr), tree_right(nullptr), dad(nullptr) {}

	AVLtree(Value* new_value, Key* new_key): tree_value(new_value),tree_key(new_key), tree_bf(0) , tree_height(1), tree_size(1), tree_extra_content(*new_key),tree_left(
			nullptr), tree_right(nullptr), dad(nullptr) {}

	void operator+(AVLtree<Value, Key>& tree)
	{
		int all_size= this->getsize() + tree.getsize();
		Value* t_values_holder[this->getsize()];
		Key* t_keys_holder[this->getsize()];
		int* i = new int(0);
		this->inorder_insert(t_values_holder, t_keys_holder, i);
		delete i;
		Value* sec_values_holder[tree.getsize()];
		Key* sec_keys_holder[tree.getsize()];
		int* j = new int(0);
		tree.inorder_insert(sec_values_holder, sec_keys_holder, j);
		delete j;
		Value** new_keys = new Value*[all_size];
		Value** final_values_arr = (this->array_merge(t_values_holder, sec_values_holder,t_keys_holder,sec_keys_holder, all_size, this->getsize(), tree.getsize(), new_keys));
		this->empty_tree();
		this->arr_to_tree(final_values_arr, new_keys, 0 ,all_size-1);
		delete[] final_values_arr;
		delete[] new_keys;
	}  //freed  //done

	void empty_tree()
	{
		this->set_info(nullptr);
		this->set_key(nullptr);
		this->setdad(nullptr);
		this->tree_extra_content = 0;
		this->tree_size =1 ;
		this->tree_bf = 0;
		this->tree_height = 1;
		if(this->get_left()){
			(this->get_left())->empty_tree();
			delete this->get_left();
		}
		if(this->get_right()){
			(this->get_right())->empty_tree();
			delete this->get_right();
		}
		this->set_right(nullptr);
		this->set_left(nullptr);
	}

	void arr_to_tree(Value* arr_values[],Key* arr_keys[], int start, int end)    //makes an AVL tree from a sorted array, recursive function
	{
		if(start==end)
		{
			this->set_info(arr_values[start]);
			this->set_key(arr_keys[start]);
			this->increase_extra(*arr_keys[start]);
		}
		if(start < end)
		{
			int head = (start + end) / 2;
			this->set_info(arr_values[head]);
			this->set_key(arr_keys[head]);
			this->increase_extra(*arr_keys[head]);
			if(end-head>=1)
			{
				AVLtree<Value,Key>* right(new AVLtree<Value,Key>());
				this->set_right(right);
				this->get_right()->setdad(this);
				this->get_right()->arr_to_tree(arr_values, arr_keys, head + 1, end);
			}
			if(head-start>=1)
			{
				AVLtree<Value,Key>* left(new AVLtree<Value,Key>());
				this->set_left(left);
				this->get_left()->setdad(this);
				(this->get_left())->arr_to_tree(arr_values, arr_keys, start, head-1);

			}
			this->fix_heights();
		}

	}      //done and shared //freed

	Value** array_merge(Value* value_a[],Value* value_b[],Key* key_a[], Key* key_b[], int total_size, int a_size, int b_size, Key* new_keys[])  //simply takes two arrays and merge them to the first one
	{

		Value** new_values = new Value*[total_size];
		int a_count=0;
		int b_count=0;
		int size_b = b_size;
		int size_a = a_size;
		for(int i=0; i<total_size;i++)
		{
			if( a_count < size_a && b_count<size_b) {
				if (*key_a[a_count] < *key_b[b_count]) {
					new_keys[i] = key_a[a_count];
					new_values[i] = value_a[a_count];
					a_count++;
				} else {
					new_keys[i] = key_b[b_count];
					new_values[i] = value_b[b_count];
					b_count++;
				}
			}
			else if(a_count<size_a)
			{
				new_keys[i] = key_a[a_count];
				new_values[i] = value_a[a_count];
				a_count++;
			}
			else if(b_count<size_b)
			{
				new_keys[i] = key_b[b_count];
				new_values[i] = value_b[b_count];
				b_count++;
			}
		}
		return new_values;
	}        //done //freed

	void inorder_insert(Value* arr_values[],Key* arr_keys[] ,int* i)//get an array and put the tree in the array inorder
	{
		if(this->get_left())
		{
			(this->get_left())->inorder_insert(arr_values, arr_keys, i);
		}
		arr_values[*i] = this->getinfo();
		arr_keys[*i] = this->get_key();
		(*i)++;
		if(this->get_right())
		{
			(this->get_right())->inorder_insert(arr_values, arr_keys, i);
		}
	}   //freed  //done

	void postorder_insert(Value* arr_values[],Key* arr_keys[] ,int* i)//get an array and put the tree in the array inorder
	{
		if(this->get_right())
		{
			(this->get_right())->postorder_insert(arr_values, arr_keys, i);
		}
		arr_values[*i] = this->getinfo();
		arr_keys[*i] = this->get_key()
		(*i)++;
		if(this->get_left())
		{
			(this->get_left())->postorder_insert(arr_values, arr_keys, i);
		}
	}   //freed  //done

	int getsize()   //return the size of the tree
	{
		if(!(this->getinfo()))
		{
			return 0;
		}
		return this->tree_size;
	}      //done and freed

	Value* getinfo()        //returns the value of the object, might be Group, Player etc...
	{
		return this->tree_value;
	}        //done and freed

	tree_result add_object(Value* new_value, Key* new_key)      //gets info and finds his place in the tree, creating an object and adds it to his right place while keeping the order by flipping
	{
		if(this->getinfo()) {
			if (*new_key == *(this->get_key())){
				return ALREADY_EXIST;
			}
			else if (*(this->get_key()) < *new_key){             //bigger
				if (!(this->get_right())){                     //nothing on the right
					AVLtree<Value,Key>* new_tree(new AVLtree<Value,Key>(new_value, new_key));
					this->set_right(new_tree);
					new_tree->setdad(this);
					this->fix_heights();
				}
				else{                            //the tree kept going right
					tree_result result = ((this->get_right())->add_object(new_value, new_key));
					this->fix_heights();
					if (result != TREE_SUCCESS){
						return result;
					}
				}
			}
			else{                                 //smaller
				if (!(this->get_left())){           //nothing on the right
					AVLtree<Value,Key>* new_tree(new AVLtree<Value,Key>(new_value, new_key));
					this->set_left(new_tree);
					new_tree->setdad(this);
					this->fix_heights();
				}
				else{                            //the tree kept going right
					tree_result result = ((this->get_left())->add_object(new_value, new_key));
					this->fix_heights();
					if (result != TREE_SUCCESS) {
						return result;
					}
				}
			}
			this->fix_tree();
			return TREE_SUCCESS;
		}
		else{
			this->set_info(new_value);
			this->set_key(new_key);
			this->tree_extra_content = *new_key;
			return TREE_SUCCESS;
		}
	} //freed

	int get_bf(){
		return this->tree_bf;
	} //freed

	void fix_tree(){
		if(this->tree_bf == 2){
			if(this->tree_left->get_bf()>=0){
				this->flip_right();
			}
			else if((this->get_left())->tree_bf== -1){
				(this->get_left())->flip_right(true);
				this->flip_right();
			}
		}
		else if(this->tree_bf == -2){
			if(this->get_right()->tree_bf == 1){
				(this->get_right())->flip_right(false);
				this->flip_right(true);
			}
			else if((this->get_right())->tree_bf <=0){
				this->flip_right(true);
			}
		}
	}

	void fix_tree_hard(){
		this->fix_heights();
		this->fix_tree();
		if(this->dad)
			(this->dad)->fix_tree_hard();
	}

	void delete_object( Key* search_key){      //deletes an object after finding it, keeps the order by flipping
		AVLtree<Value, Key>* to_replace;
		to_replace = (this->find_object(search_key));
		if(!(to_replace->get_right()) && !(to_replace->get_left())){
			if (to_replace->getdad()){
				AVLtree<Value,Key>* father = to_replace->getdad();
				if ((to_replace->getdad()->get_right())){
					if(*((to_replace->getdad()->get_right())->get_key()) == *search_key) {
						to_replace->getdad()->set_right(nullptr);
					}
					else{
						to_replace->getdad()->set_left(nullptr);
					}
				}
				else
					to_replace->getdad()->set_left(nullptr);
				to_replace->setdad(nullptr);
				delete to_replace;
				father->fix_tree_hard();
			}
			else
				to_replace->empty_tree();
		}
		else if(!(to_replace->get_right()) && (to_replace->get_left())){
			AVLtree<Value,Key>* replacement = to_replace->get_left();
			to_replace->set_info(replacement->getinfo());
			to_replace->set_key(replacement->get_key());
			to_replace->set_left(replacement->get_left());
			to_replace->set_right(replacement->get_right());
			replacement->set_left(nullptr);
			replacement->set_right(nullptr);
			replacement->set_info(nullptr);
			replacement->set_key(nullptr);
			delete replacement;
			to_replace->fix_tree_hard();
		}
		else if((to_replace->get_right()) && !(to_replace->get_left())){
			AVLtree<Value,Key>* replacement = to_replace->get_right();
			to_replace->set_info(replacement->getinfo());
			to_replace->set_key(replacement->get_key());
			to_replace->set_left(replacement->get_left());
			to_replace->set_right(replacement->get_right());
			replacement->set_left(nullptr);
			replacement->set_right(nullptr);
			replacement->set_info(nullptr);
			delete replacement;
			to_replace->fix_tree_hard();
		}
		else{
			(to_replace->get_right())->replace_next_object(to_replace);
		}
	}    //done and freed

	tree_result replace_next_object(AVLtree<Value,Key>* to_delete){
		if(!this->get_left())
		{
			to_delete->set_info((this->getinfo()));
			to_delete->set_key(this->get_key());
			if(this->get_right()){
				AVLtree<Value,Key>* temp_right = this->get_right();
				this->set_info((this->get_right())->getinfo());
				this->set_key((this->get_right())->get_key());
				this->set_left((this->get_right())->get_left());
				this->set_right((this->get_right())->get_right());
				if(this->get_right()){
					this->get_right()->setdad(this);
				}
				if(this->get_left()){
					this->get_left()->setdad(this);
				}
				temp_right->set_left(nullptr);
				temp_right->set_right(nullptr);
				temp_right->set_info(nullptr);
				temp_right->set_key(nullptr);
				delete temp_right;
				this->fix_heights();
				this->fix_tree_hard();
			}
			else{
				to_delete->set_info(this->getinfo());
				to_delete->set_key(this->get_key());
				AVLtree<Value,Key>* father = this->dad;
				if(this->getdad()->get_right()) {
					if (*((this->getdad()->get_right())->get_key()) == *(this->get_key())) {
						father->set_right(nullptr);
					}
					else{
						father->set_left(nullptr);
					}
				}
				else {
					father->set_left(nullptr);
				}
				this->setdad(nullptr);
				this->set_info(nullptr);
				this->set_key(nullptr);
				this->tree_height=0;
				this->tree_size=0;
				delete this;
				father->fix_heights();
				father->fix_tree_hard();
			}
			return TREE_SUCCESS;
		}
		else{
			tree_result p = (this->get_left())->replace_next_object(to_delete);
			return p;
		}

	}

	AVLtree<Value,Key>* find_object( Key* search_key){
		if(!(this->getinfo())){
			return nullptr;
		}
		if(*(this->get_key()) == *search_key){
			return this;
		}
		else if((*(this->get_key())< *search_key)){
			if(!(this->get_right())){
				return nullptr;
			}
			return (this->get_right())->find_object(search_key);
		}
		else{

			if(!(this->get_left())){
				return nullptr;
			}
			return (this->get_left())->find_object(search_key);
		}
	}

	AVLtree<Value,Key>* get_left(bool flipped = false){
		if(flipped)
			return tree_right;
		return tree_left;
	}

	AVLtree<Value,Key>* get_right(bool flipped = false){
		if(!flipped)
			return tree_right;
		return tree_left;
	}             



	void DestroyRecursive() {
		if(this->get_right()){
			this->get_right()->DestroyRecursive();
			this->get_right()->set_info(nullptr);
			delete this->get_right();
			this->set_right(nullptr);
		}
		if(this->get_left()){
			this->get_left()->DestroyRecursive();
			this->get_left()->set_info(nullptr);
			delete this->get_left();
			this->set_left(nullptr);
		}
	}

	~AVLtree() {
		delete tree_right;
		delete tree_left;
	}


};


#endif //NEW_TREE_AVL_NEW_AVL_TREE_H
