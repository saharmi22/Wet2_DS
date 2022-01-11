//
// Created by sahar on 09/01/2022.
//

#include "Group.h"

void Group::addPlayer(Player *player_to_add) {      //todo

}

void Group::removePlayer(int id_to_remove) {  //todo

}


void Group::increaseCounter()
{
    this->number_of_not_included++;
}

void Group::decreaseCounter()
{
    this->number_of_not_included--;
}

AVLtree<Player, DoubleKey> *Group::getPlayers() {
    return this->players_by_level_tree;
}

Group::Group(int id) {

}

Group::~Group() {

}

AVLtree<Player, DoubleKey> **Group::getPlayersByScoreArray() {
    return this->players_by_score_array;
}
