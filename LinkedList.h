//
// Created by sahar on 15/01/2022.
//

#ifndef WET2_DS_LINKEDLIST_H
#define WET2_DS_LINKEDLIST_H

#include "HashTableNode.h"

template <typename T>
class LinkedList {
    HashTableNode<T>* data;
    LinkedList<T>* next;
    int size;
public:
    LinkedList() : data(nullptr), next(nullptr), size(0){}

    int getSize() const {
        return size;
    }

    HashTableNode<T> *getData() const {
        return data;
    }

    LinkedList<T> *getNext() const {
        return next;
    }

    T* GetMember(int key){
        if(this) {
			if (this->data->GetKey() == key)
				return this->data;
			else
				return this->next->GetMember(key);
		}
        return nullptr;
    }

    void Insert(HashTableNode<T>* last){
        if (!this->next)
            this->next = last;
        else this->next->Insert(last);
        size++;
    }

    void Delete(int key)
    {
        if (this->next) {
            if (this->next->data->GetKey() == key) {
                delete this->next;
                this->next = this->next->next;
                size--;
            } else
                this->next->Delete(key);
        }
    }
};


#endif //WET2_DS_LINKEDLIST_H
