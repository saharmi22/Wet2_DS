#include <iostream>
#include "HashTable.h"

int main() {
    HashTable<int>* ht = new HashTable<int>();
    int data_1 = 1;
    int data_2 = 2;
    int data_3 = 3;
    int data_4 = 4;
    int data_5 = 5;
    int data_6 = 6;
    int data_7 = 7;
    int data_8 = 8;
    ht->Insert(1, &data_1);
    ht->Insert(2, &data_2);
    ht->Insert(3, &data_3);
    ht->Insert(4, &data_4);
    ht->Insert(5, &data_5);
    ht->Insert(6, &data_6);
    ht->Insert(7, &data_7);
    ht->Insert(8, &data_8);
    ht->Delete(2);
    ht->Delete(1);
    ht->Delete(3);
    ht->Delete(7);
    ht->Delete(4);
    ht->Delete(5);
    ht->Member(7);
    ht->Member(6);
    delete ht;
}
