//
// Created by sahar on 10/01/2022.
//

#ifndef WET2_DS_DOUBLEKEY_H
#define WET2_DS_DOUBLEKEY_H


class DoubleKey {

    int first_key;
    int second_key;

public:

    DoubleKey(int first, int second);
    int getFirst();
    int getSecond();
    bool operator<(const DoubleKey& key2) const;
    bool operator==(const DoubleKey& key2) const;
    void setFirst(int set_to);

};


#endif //WET2_DS_DOUBLEKEY_H
