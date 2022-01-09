//
// Created by sahar on 05/01/2022.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "HashTableNode.h"

template <typename T>
class HashTable {
private:
    int table_size;
    int num_of_items;
    HashTableNode<T> **table;

    int h(int key) {
        return (key % this->table_size);
    }

    int r(int key) {
        return (1 + (key % 3));
    }

    void rehash() {
        int original_size = this->table_size;
        int r0, index;
        if (this->num_of_items >= this->table_size)
            this->table_size *= 2;
        else
            this->table_size /= 2;
        HashTableNode<T> **new_table = new HashTableNode<T> *(this->table_size);
        for (int i = 0; i < original_size; i++) {
            r0 = r(this->table[i].GetKey());
            index = h(this->table[i].GetKey());
            if (this->num_of_items >= this->table_size)
                rehash();
            while (!this->table[index]->GetData()) {
                index = h(index + r0);
            }
            HashTableNode<T> *new_node = new HashTableNode<T>(this->table[i].GetKey(), this->table[i]->GetData());
            this->table[i]->SetData();
            new_table[index] = new_node;
        }
        delete this->table;
        this->table = new_table;
    }

public:
    ~HashTable() = default;

    HashTable() : num_of_items(0), table_size(7), table(new HashTableNode<T> *(this->table_size)) {}

    void Insert(int key, T *data) {
        int r0 = r(key);
        int index = h(key);
        if (!this->Member(key)) {
            if (this->num_of_items >= this->table_size)
                rehash();
            while (!this->table[index]->GetData()) {
                index = h(index + r0);
            }
            HashTableNode<T> *new_node = new HashTableNode<T>(key, data);
            this->table[index] = new_node;
            this->num_of_items++;
        }
    }


    void Delete(int key) {
        int r0 = r(key);
        int index = h(key);
        int count = 1;
        if (this->num_of_items <= this->table_size / 4 && this->table_size != 7)
            rehash();
        while (this->table[index] && this->table[index]->GetKey() != key && count <= this->table_size) {
            index = h(index + r0);
            count++;
        }
        if (count <= this->table_size && this->table[index]) {
            this->table[index]->SetKey(-1);
            this->table[index]->SetData();
            this->num_of_items--;
        }
    }

    bool Member(int key) {
        int r0 = r(key);
        int index = h(key);
        int count = 1;
        if (this->num_of_items <= this->table_size / 4)
            rehash();
        while (this->table[index] && this->table[index]->GetKey() != key && count <= this->table_size) {
            index = h(index + r0);
            count++;
        }
        return (count <= this->table_size && this->table[index]);
    }
};


#endif //HASHTABLE_HASHTABLE_H
