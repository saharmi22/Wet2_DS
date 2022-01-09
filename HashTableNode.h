//
// Created by sahar on 05/01/2022.
//

#ifndef HASHTABLE_HASHTABLENODE_H
#define HASHTABLE_HASHTABLENODE_H

template <typename T>
class HashTableNode {
private:
    int key;
    T *data;
public:
    ~HashTableNode() = default;

    HashTableNode(int key, T *data) : key(key), data(data) {}


    int GetKey() {
        return this->key;
    }


    T GetData() {
        return this->data;
    }

    bool operator==(const HashTableNode<T> &x) {
        return (this->key == x.key);
    }

    void SetData(T *data_) {
        this->data = data_;
    }

    void SetKey(int key_) {
        this->key = key_;
    }
};


#endif //HASHTABLE_HASHTABLENODE_H
