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
    HashTableNode<T>** table;

    int h(int key);
    int r(int key);
    void rehash();

public:

    HashTable();
    void Insert(int key, T* data);
    void Delete(int key);
    bool Member(int key);
    ~HashTable() = default;

};


#endif //HASHTABLE_HASHTABLE_H
