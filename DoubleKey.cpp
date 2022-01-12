//
// Created by sahar on 10/01/2022.
//

#include "DoubleKey.h"

DoubleKey::DoubleKey(int first, int second) : first_key(first), second_key(second) {}

void DoubleKey::setFirst(int set_to) {
    this->first_key = set_to;
}

bool DoubleKey::operator<(const DoubleKey &key2) const {
    if (this->first_key < key2.first_key)
        return (this->first_key < key2.first_key);
    else
        return (this->second_key < key2.second_key);
}

bool DoubleKey::operator==(const DoubleKey &key2) const {
    return (this->first_key == key2.first_key && this->second_key == key2.second_key);
}

int DoubleKey::getFirst() {
    return first_key;
}


int DoubleKey::getSecond() {
    return second_key;
}