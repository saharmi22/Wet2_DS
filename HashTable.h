//
// Created by sahar on 05/01/2022.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "AvlTree.h"
#include "DoubleKey.h"
#include "HashTableNode.h"
#include "Player.h"


class HashTable {
	int table_size;
	int num_of_items;
	AVLtree<Player, DoubleKey> **table;
public:
	HashTable():table_size(10), num_of_items(0), table(new AVLtree<Player,DoubleKey>*[10]){
		for (int i = 0; i < 10; ++i) {
			table[i] = new AVLtree<Player, DoubleKey>();
		}
	}
	void rehash() {
		int original_size = this->table_size;
		AVLtree<Player, DoubleKey> **new_table;
		new_table = new AVLtree<Player,DoubleKey>*[table_size*3]
		this->table_size = table_size * 3;
		for (int i = 0; i < original_size; ++i) {
			while(this->table[i]->getinfo()){
				int id = this->table[i]->getinfo()->getId();
				DoubleKey* new_key = new DoubleKey(id, id);
				new_table[id%this->table_size]->add_object(this->table[i]->getinfo());
				this->table[i]->delete_object(new_key);
			}
		}
		AVLtree<Player, DoubleKey> **table_to_delete = this->table;
		this->table = new_table;
		delete table_to_delete;
	}

	void Insert(int key, Player *data) {
		if (!this->Member(key)) {
			if((this->table_size*3)<this->num_of_items){
				this->rehash();
			}
			DoubleKey* new_key = new DoubleKey(key, key);
			table[(key%table_size)]->add_object(data, new_key);
		}
	}

	void Delete(int key) {
		DoubleKey* search_key = new DoubleKey(key, key);
		if(!this->table[key%(this->table_size)]->find_object(search_key)){
			this->table[key%(this->table_size)]->delete_object(search_key);
			this->num_of_items--;
		}
		delete search_key;
	}

	bool Member(int key) {
		DoubleKey* search_key = new DoubleKey(key, key);
		if(this->table[key%(this->table_size)]->find_object(search_key)){
			return true;
		}
		delete search_key;
		return true;
	}

	T* GetMember(int key)
	{
		DoubleKey* search_key = new DoubleKey(key, key);
		AVLtree<Player,DoubleKey> search_result = this->table[key%(this->table_size)]->find_object(search_key);
		delete search_key;
		if(search_result){
			return search_result.getinfo();
		}
		return search_result;
	}

	~HashTable()
	{
		for (int i = 0; i< this->table_size; i++)
			delete table[i];
	}

}

















   /*
template <typename T>
class HashTable {
    int table_size;
    int num_of_items;
    HashTableNode<T>** table;

    int findNextPrime(int x){
        for (int i = x+1; true; i++) {
            int j = 2;
            for (; j < i; j++)
                if (i % j == 0)
                    break;
            if (j == i)
                return i;
        }
    }

    int findLastPrime(int x){
        for (int i = x-1; i>0; i--) {
            int j = 2;
            for (; j < i; j++)
                if (x % j == 0)
                    break;
            if (j == i)
                return i;
        }
    }

    void rehash() {
        int original_size = this->table_size;
        int r0, h0, index, count;
        if (this->num_of_items >= this->table_size)
            this->table_size= findNextPrime(this->table_size);
        else
            this->table_size= findLastPrime(this->table_size);
        HashTableNode<T>** new_table = new HashTableNode<T>*[this->table_size];
        for (int i=0; i< this->table_size; i++)
        {
            new_table[i] = nullptr;
        }
        for (int i=0; i<original_size; i++)
        {
            if (table[i] && table[i]->GetKey() != -1) {
                r0 = r(this->table[i]->GetKey());
                h0 = h(this->table[i]->GetKey());
                index = h0;
                count = 1;
                while (new_table[index]) {
                    index = h(h0+count*r0);
                    count++;
                }
                HashTableNode<T> *new_node = new HashTableNode<T>(this->table[i]->GetKey(), this->table[i]->GetData());
                this->table[i]->SetData();
                new_table[index] = new_node;
            }
        }
        delete this->table;
        this->table = new_table;
    }

public:

    HashTable() : table_size(7), num_of_items(0) , table(new HashTableNode<T>*[this->table_size]){}

    int h(int key) {
        return (key % table_size);
    }

    int r(int key) {
        return (1+(key%(table_size-3)));
    }

    void Insert(int key, T *data) {
        if (!this->Member(key)) {
           if (this->num_of_items >= this->table_size)
                rehash(); //rehash could change h,r
            int r0 = r(key);
            int h0 = h(key);
            int index = h0;
            int count = 1;
            while (this->table[index] && this->table[index]->GetKey() != -1) {
                index = (h0 + count*r0)% this->table_size;
                count++;
            }
            HashTableNode<T> *new_node = new HashTableNode<T>(key, data);
            this->table[index] = new_node;
            this->num_of_items++;
        }
    }

    void Delete(int key) {
       if (2*this->num_of_items <= findLastPrime(this->table_size) && this->table_size!=7)
            rehash(); //rehash could change h,r
        int r0 = r(key);
        int h0 = h(key);
        int index = h0;
        int count = 1;
        while (this->table[index] && this->table[index]->GetKey()!=key && count <= this->table_size)
        {
            index = (h0+count * r0)% this->table_size;
            count++;
        }
        if (count <= this->table_size && this->table[index])
        {
            this->table[index]->SetKey(-1);
            this->table[index]->SetData();
            this->num_of_items--;
        }
    }

    bool Member(int key) {
        int r0 = r(key);
        int h0 = h(key);
        int index = h0;
        int count = 1;
        while (this->table[index] && this->table[index]->GetKey()!=key && count <= this->table_size)
        {
            index = (h0 + count*r0)% this->table_size;
            count++;
        }
        return (count <= this->table_size && this->table[index]);
    }

    T* GetMember(int key)
    {
        int r0 = r(key);
        int h0 = h(key);
        int index = h0;
        int count = 1;
        while (this->table[index] && this->table[index]->GetKey()!=key && count <= this->table_size)
        {
            index = (h0 + count*r0)% this->table_size;
            count++;
        }
        if (count <= this->table_size && this->table[index])
            return this->table[index]->GetData();
        return nullptr;
    }

    ~HashTable()
    {
        for (int i = 0; i< this->table_size; i++)
            delete table[i];
    }
};      */

#endif //HASHTABLE_HASHTABLE_H
