//
// Created by sahar on 05/01/2022.
//

#include "HashTable.h"

template<typename T>
HashTable<T>::HashTable() : num_of_items(0), table_size(7), table(new HashTableNode<T>*(this->table_size)){}

template<typename T>
int HashTable<T>::h(int key) {
    return (key % this->table_size);
}

template<typename T>
int HashTable<T>::r(int key) {
    return (1+(key%3));
}

template<typename T>
void HashTable<T>::rehash() {
    int original_size = this->table_size;
    int r0, index;
    if (this->num_of_items >= this->table_size)
        this->table_size*=2;
    else
        this->table_size/=2;
    HashTableNode<T>** new_table = new HashTableNode<T>*(this->table_size);
    for (int i=0; i<original_size; i++)
    {
        r0 = r(this->table[i].GetKey());
        index = h(this->table[i].GetKey());
        if (this->num_of_items >= this->table_size)
            rehash();
        while (!this->table[index]->GetData())
        {
            index = h(index+r0);
        }
        HashTableNode<T>* new_node = new HashTableNode<T>(this->table[i].GetKey(), this->table[i]->GetData());
        this->table[i]->SetData();
        new_table[index] = new_node;
    }
    delete this->table;
    this->table = new_table;
}

template<typename T>
void HashTable<T>::Insert(int key, T *data) {
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

template<typename T>
void HashTable<T>::Delete(int key) {
    int r0 = r(key);
    int index = h(key);
    int count = 1;
    if (this->num_of_items <= this->table_size/4 && this->table_size!=7)
        rehash();
    while (this->table[index] && this->table[index]->GetKey()!=key && count <= this->table_size)
    {
        index = h(index+r0);
        count++;
    }
    if (count <= this->table_size && this->table[index])
    {
        this->table[index]->SetKey(-1);
        this->table[index]->SetData();
        this->num_of_items--;
    }
}

template<typename T>
bool HashTable<T>::Member(int key) {
    int r0 = r(key);
    int index = h(key);
    int count = 1;
    if (this->num_of_items <= this->table_size/4)
        rehash();
    while (this->table[index] && this->table[index]->GetKey()!=key && count <= this->table_size)
    {
        index = h(index+r0);
        count++;
    }
    return (count <= this->table_size && this->table[index]);
}
