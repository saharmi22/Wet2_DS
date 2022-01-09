//
// Created by sahar on 05/01/2022.
//

#ifndef HASHTABLE_HASHTABLENODE_H
#define HASHTABLE_HASHTABLENODE_H

template <typename T>
class HashTableNode {
private:
    int key;
    T* data;
public:
    HashTableNode(int key, T* data);
    int GetKey();
    T* GetData();
    void SetData(T* data_ = nullptr);
    void SetKey(int key_);
    bool operator==(const HashTableNode<T>& x);
    ~HashTableNode() = default;
};


#endif //HASHTABLE_HASHTABLENODE_H
