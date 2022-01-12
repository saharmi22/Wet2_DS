//
// Created by sahar on 09/01/2022.
//

#include "Group.h"

void Group::addPlayer(Player *player_to_add) {      
	DoubleKey* new_key = new DoubleKey(player_to_add->getLevel(), player_to_add->getId());
	players_by_score_array[player_to_add->getScore()]->add_object(player_to_add, new_key);
	players_by_level_tree->add_object(player_to_add, new_key);
	not_included_score_arr[player_to_add->getScore()]++;
}

void Group::removePlayer(int id_to_remove, int level, int score) {
	DoubleKey* search_key = new DoubleKey(level, id_to_remove);
	if(level==0){
		not_included_score_arr[score]--;
		delete search_key;
	}
	else {
		Player *player_to_delete = players_by_level_tree->find_object(search_key)->getinfo();
		players_by_score_array[player_to_delete->getScore()]->delete_object(search_key);
		players_by_level_tree->delete_object(search_key);
		delete search_key;
	}
}


void Group::increaseCounter(int score_to_add)
{
    this->number_of_not_included++;
    not_included_score_arr[score_to_add]++;
}

void Group::decreaseCounter(int score_to_dec)
{
    this->number_of_not_included--;
	not_included_score_arr[score_to_dec]--;
}

AVLtree<Player, DoubleKey> *Group::getPlayers() {
    return this->players_by_level_tree;
}

int Group::getAmountZero(){
	return this->number_of_not_included;
}

int Group::getAmountZeroScore(int score_to_find){
	return not_included_score_arr[score_to_find];
}


Group::Group(int id):group_id(id), number_of_not_included(0),
						players_by_score_array(new AVLtree<Player,DoubleKey>*[200]),
							players_by_level_tree(new AVLtree<Player,DoubleKey>) {
	for (int i = 0; i < 200; ++i) {
		players_by_score_array[i] = new AVLtree<Player,DoubleKey>();
		not_included_score_arr[i] = 0;
	}




}

Group::~Group() {
	delete players_by_level_tree;

}

AVLtree<Player, DoubleKey> **Group::getPlayersByScoreArray() {
    return this->players_by_score_array;
}
