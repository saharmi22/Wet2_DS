//
// Created by sahar on 09/01/2022.
//

#ifndef WET2_DS_GROUP_H
#define WET2_DS_GROUP_H
#include "AvlTree.h"
#include "Player.h"
#include "DoubleKey.h"

class Group {
    int group_id;
    int number_of_not_included;
    AVLtree<Player,DoubleKey>** players_by_score_array;
    AVLtree<Player, DoubleKey>* players_by_level_tree;
	int not_included_score_arr[201];

public:
    explicit Group(int id);
    void addPlayer(Player* player_to_add);
    void removePlayer(int id_to_remove, int level, int score);
    void removePlayer_fake(int id_to_remove, int level, int score);
    AVLtree<Player, DoubleKey>* getPlayers();
    AVLtree<Player, DoubleKey>** getPlayersByScoreArray();
    void increaseCounter(int score_to_add);
    void decreaseCounter(int score_to_dec);
    int getAmountZero();
	int getAmountZeroScore(int score_to_find);
    int *getNotIncludedScoreArr();
    void setNumberOfNotIncluded(int numberOfNotIncluded);
    int getId();
    ~Group();
};


#endif //WET2_DS_GROUP_H
