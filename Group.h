//
// Created by sahar on 09/01/2022.
//

#ifndef WET2_DS_GROUP_H
#define WET2_DS_GROUP_H
#include "AvlTree.h"
#include "Player.h"
#include "DoubleKey.h"

class Group {
private:
    int group_id;
    int number_of_not_included;
    AVLtree<Player,DoubleKey>** players_by_score_array;
    AVLtree<Player, DoubleKey>* players_by_level_tree;

public:
    void addPlayer(Player* player_to_add);
    void removePlayer(int id_to_remove);
    Player* changePlayersScore(DoubleKey key, int amount_to_increase);
    Player* changePlayersLevel(DoubleKey key, int amount_to_increase);
    double getPercent(int score, int lower_level, int higher_level);
    void increaseCounter();
    void decreaseCounter();
};


#endif //WET2_DS_GROUP_H
