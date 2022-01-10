//
// Created by sahar on 09/01/2022.
//

#include "Group.h"

void Group::addPlayer(Player *player_to_add) {
    DoubleKey* new_key = new DoubleKey(player_to_add->getLevel(), player_to_add->getId());
    players_by_level_tree->add_object(player_to_add, new_key);


}

void Group::removePlayer(int id_to_remove) {

}

Player *Group::changePlayersScore(DoubleKey key, int amount_to_increase) {
    return nullptr;
}

Player *Group::changePlayersLevel(DoubleKey key, int amount_to_increase) {
    return nullptr;
}

double Group::getPercent(int score, int lower_level, int higher_level) {
    return 0;
}

void Group::increaseCounter()
{
    this->number_of_not_included++;
}

void Group::decreaseCounter()
{
    this->number_of_not_included--;
}
