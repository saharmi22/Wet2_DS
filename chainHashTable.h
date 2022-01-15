//
// Created by sahar on 15/01/2022.
//

#ifndef WET2_DS_CHAINHASHTABLE_H
#define WET2_DS_CHAINHASHTABLE_H

#include "LinkedList.h"

template <typename T>
class chainHashTable {
    LinkedList<T>** table;
    int table_size;
    int num_of_items;
public:
    int h(int key){
        return key%table_size;
    }

    void rehash(){
        int original_size = this->table_size;
        if (this->table_size != 7) {
            if (this->table_size >= 4 * this->num_of_items)
                this->table_size *= 2;
            else
                this->table_size /= 2;
            LinkedList<T> **new_table = new LinkedList<T> *[table_size];
            for (int i = 0; i < table_size; i++) {
                new_table[i] = new LinkedList<T>();
            }
            for (int i = 0; i < original_size; i++){
                while (table[i]->getNext())
                    new_table[h(table[i]->getNext()->getKey())]->Insert(table[i]->getData());
                table[i]->getData = nullptr;
            }
            delete table;
            this->table = new_table;
        }
    }

    chainHashTable() : table(new LinkedList<T>*[7]), table_size(7), num_of_items(0){
        for (int i=0; i<7; i++)
            table[i] = new LinkedList<T>();
    }

    void Insert(int key, T* data){
        if (this->table_size >= 4* this->num_of_items)
            rehash();
        HashTableNode<T>* node = new HashTableNode<T>(key, data);
        this->table[h(key)]->Insert(node);
    }

    void Delete(int key){
        if (this->num_of_items*2 <= this->table_size)
            rehash();
        this->table->Delete(key);
    }

    T* GetMember(int key){
        return table[h(key)]->GetMember(key);
    }
};


#endif //WET2_DS_CHAINHASHTABLE_H
