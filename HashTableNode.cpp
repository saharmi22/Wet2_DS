//
// Created by sahar on 05/01/2022.
//

#include "HashTableNode.h"

template<typename T>
HashTableNode<T>::HashTableNode(int key, T* data) : key(key), data(data) {}

template<typename T>
int HashTableNode<T>::GetKey() {
    return this->key;
}

template<typename T>
T *HashTableNode<T>::GetData() {
    return this->data;
}

template<typename T>
bool HashTableNode<T>::operator==(const HashTableNode<T> &x) {
    return (this->key == x.key);
}

template<typename T>
void HashTableNode<T>::SetData(T *data_) {
    this->data = data_;
}

template<typename T>
void HashTableNode<T>::SetKey(int key_) {
    this->key = key_;
}
