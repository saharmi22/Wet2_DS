//
// Created by sahar on 05/01/2022.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "HashTableNode.h"

template <typename T>
class HashTable {
    int table_size;
    int num_of_items;
    HashTableNode<T>** table;

    void rehash() {
        int original_size = this->table_size;
        int r0, h0, index, count;
        if (this->num_of_items >= this->table_size)
            this->table_size*=2;
        else
            this->table_size/=2;
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

    HashTable() : table_size(73), num_of_items(0) , table(new HashTableNode<T>*[this->table_size]){}

    int h(int key) {
        return (key % table_size);
    }

    int r(int key) {
        return (1+(key%(5)));
    }

    void Insert(int key, T *data) {
        if (!this->Member(key)) {
           /* if (this->num_of_items >= this->table_size)
                rehash(); //rehash could change h,r */
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
       /* if (this->num_of_items <= this->table_size/4 && this->table_size!=7)
            rehash(); //rehash could change h,r   */
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
};

#endif //HASHTABLE_HASHTABLE_H
