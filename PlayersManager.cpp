//
// Created by sahar on 10/01/2022.
//

#include "PlayersManager.h"

PlayersManager::PlayersManager(int k, int scale){

	players_by_id = new HashTable<Player>();
	players_by_level = new AVLtree<Player, DoubleKey>();
	players_by_score = new AVLtree<Player, DoubleKey>*[200];
	for (int i = 0; i < 200; ++i) {
		players_by_score[i] = new AVLtree<Player, DoubleKey>();
		not_included_score_arr[i] = 0;
	}
	groups = new UnionFind<Group>(k);
	num_of_groups = k;
	number_of_not_included = 0;
	this->scale= scale;
}

//valid parameters
//merge groups in union
//merge trees of players
StatusType PlayersManager::MergeGroups(int GroupID1, int GroupID2)      // update not_included_score_arr
{
    if (GroupID1<=0 || GroupID1> this->num_of_groups || GroupID2<=0 || GroupID2> this->num_of_groups)
        return INVALID_INPUT;
	Group* group1;
	Group* group2;
	group1 = this->groups->get_union(GroupID1);
	group2 = this->groups->get_union(GroupID2);
    this->groups->to_union(GroupID1, GroupID2);
    *group2->getPlayers() + *group1->getPlayers();        //check size
    for (int i=0; i< this->scale; i++)
    {
        *group1->getPlayersByScoreArray()[i] + *group2->getPlayersByScoreArray()[i];    //delete
    }
    return SUCCESS;
}

StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int score){      //done
	if(PlayerID<=0 ||GroupID<=0||score<=0||score>scale||GroupID>num_of_groups)
		return INVALID_INPUT;
	if((players_by_id->GetMember(PlayerID)))
		return FAILURE;
	Player* new_player = new Player(PlayerID, score, GroupID);
	players_by_id->Insert(PlayerID, new_player);
	(groups->get_union(GroupID))->increaseCounter(score);
	number_of_not_included++;
	not_included_score_arr[score]++;
	return SUCCESS;
}

//valid parameters
//check if player exists in hash
//remove players from group's dss
//check if is in by score and by level and if not decrease num of not included
//remove player from system's dss
StatusType PlayersManager::RemovePlayer(int PlayerID)        // update not_included_score_arr
{
    if (PlayerID <= 0)
        return INVALID_INPUT;
    Player* player = this->players_by_id->GetMember(PlayerID);
    if (player) {
        Group* group = this->groups->get_union(player->getGroupId());
        DoubleKey players_double_by_level(player->getLevel(), player->getId());
        group->removePlayer(PlayerID, player->getLevel(), player->getScore());
        if (this->players_by_level->find_object(&players_double_by_level)) {
            this->players_by_score[player->getScore() - 1]->delete_object(&players_double_by_level);
            this->players_by_level->delete_object(&players_double_by_level);
        }
        else
            this->number_of_not_included--;
        this->players_by_id->Delete(PlayerID);
        return SUCCESS;
    }
    return FAILURE;

}

StatusType PlayersManager::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease){
	if(PlayerID<=0||LevelIncrease<=0)
		return INVALID_INPUT;
	Player* player_to_increase = players_by_id->GetMember(PlayerID);
	if(!player_to_increase)
		return FAILURE;
	int GroupId = player_to_increase->getGroupId();
	if(player_to_increase->getLevel()==0){
		player_to_increase->addToLevel(LevelIncrease);
		int new_level = player_to_increase->getLevel();
		 not_included_score_arr[player_to_increase->getScore()]--;
		number_of_not_included--;
		(groups->get_union(GroupId))->decreaseCounter(player_to_increase->getScore());
		DoubleKey* new_key = new DoubleKey(PlayerID, new_level);
		players_by_level->add_object(player_to_increase, new_key);
		players_by_score[GroupId]->add_object(player_to_increase, new_key);
		groups->get_union(GroupId)->addPlayer(player_to_increase);   //change group accordingly
	}
	else{
		DoubleKey* temp = new DoubleKey(PlayerID, player_to_increase->getLevel());
		DoubleKey* to_delete = players_by_level->find_object(temp)->get_key();
		players_by_level->delete_object(temp);
		players_by_score[GroupId]->delete_object(temp);
		groups->get_union(GroupId)->removePlayer(PlayerID, player_to_increase->getLevel(), player_to_increase->getScore());
		temp->setFirst(player_to_increase->getLevel()+LevelIncrease);
		delete to_delete;
		players_by_level->add_object(player_to_increase, temp);
		players_by_score[GroupId]->add_object(player_to_increase, temp);
		groups->get_union(GroupId)->addPlayer(player_to_increase);
	}
	return SUCCESS;



}

//valid parameters
//check if player exists in hash, save prev score, update score
//check if appears in score array, if not add to dss
//remove and add to the right cell in score array
StatusType PlayersManager::ChangePlayerIDScore(int PlayerID, int NewScore)
{
    if (PlayerID<=0 || NewScore<=0 || NewScore >= this->scale)
        return INVALID_INPUT;
    Player* player = this->players_by_id->GetMember(PlayerID);
    if (player)
    {
        int old_score  = player->getScore();
        player->setScore(NewScore);
        DoubleKey* players_double_by_level = new DoubleKey(player->getLevel(), player->getId());
        if (!this->players_by_score[old_score]->find_object(players_double_by_level)) {
            this->players_by_score[old_score]->add_object(player, players_double_by_level);
            this->players_by_level->add_object(player, players_double_by_level);
            this->number_of_not_included--;
        }
        else {
            this->players_by_score[old_score]->delete_object(players_double_by_level);
            this->players_by_score[NewScore]->add_object(player, players_double_by_level);
        }
        return SUCCESS;
    }
    return FAILURE;
}

StatusType PlayersManager::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,double * players){
	if(GroupID<0||GroupID>num_of_groups||!players)
		return INVALID_INPUT;
	if(GroupID==0){
		double amount_level = players_by_level->find_level(lowerLevel) - players_by_level->find_level(higherLevel);
		double amount_score = players_by_score[score]->find_level(lowerLevel) - players_by_score[score]->find_level(higherLevel+1);
		if(lowerLevel==0){
			amount_level += number_of_not_included;
			amount_score += not_included_score_arr[score];
		}
		if(amount_level==0){
			return FAILURE;
		}
		double percentage = amount_score/amount_level;
		*players = percentage;
	}
	else{
		Group* group_to_pre = groups->get_union(GroupID);
		AVLtree<Player,DoubleKey>** players_by_score_array = group_to_pre->getPlayersByScoreArray();
		AVLtree<Player, DoubleKey>* players_by_level_tree= group_to_pre->getPlayers();
		double amount_level = players_by_level_tree->find_level(lowerLevel) - players_by_level_tree->find_level(higherLevel);
		double amount_score = players_by_score_array[score]->find_level(lowerLevel) - players_by_score_array[score]->find_level(higherLevel);
		if(lowerLevel==0)
		{
			amount_level += group_to_pre->getAmountZero();
			amount_score += group_to_pre->getAmountZeroScore(score);
		}
		if(amount_level==0){
			return FAILURE;
		}
		double percentage = amount_score/amount_level;
		*players = percentage;
	}
	 return SUCCESS;

}

//valid parameters
//if groupid > 0 find group
//find sum of highest m and divide by m
StatusType PlayersManager::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level) {
	if (GroupID < 0 || GroupID > this->num_of_groups || m <= 0 || !level)
		return INVALID_INPUT;
	if (GroupID > 0) {
		Group *group = this->groups->get_union(GroupID);
		AVLtree<Player, DoubleKey> *players = group->getPlayers();
		if (players->getsize() >= m) {
			*level = players->getMSum(m) / m;
			return SUCCESS;
		}
	}
	else {
		if (this->players_by_level->getsize() >= m) {
			*level = this->players_by_level->getMSum(m) / m;
			return SUCCESS;
		}
	}
	return FAILURE;
}


//BONUS
StatusType PlayersManager::GetPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers, int * HigherBoundPlayers)
{
	      return SUCCESS;
}

PlayersManager::~PlayersManager()= default;
	


