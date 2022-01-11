//
// Created by sahar on 10/01/2022.
//

#include "PlayersManager.h"

PlayersManager::PlayersManager(int k, int scale)
{

}

//valid parameters
//merge groups in union
//merge trees of players
StatusType PlayersManager::MergeGroups(int GroupID1, int GroupID2)
{
    if (GroupID1<=0 || GroupID1> this->num_of_groups || GroupID2<=0 || GroupID2> this->num_of_groups)
        return INVALID_INPUT;
    this->groups->to_union(GroupID1, GroupID2);
    Group* group1, group2;
    group1 = this->groups->get_union(GroupID1);
    group2 = this->groups->get_union(GroupID2);
    group1->getPlayers() + group2->getPlayers();
    for (i=0; i< this->scale; i++)
    {
        group1->getPlayersByScore()[i]+group2->getPlayersByScore()[i];
    }
    return SECCESS;
}

void PlayersManager::AddPlayer(int PlayerID, int GroupID, int score)
{

}

//valid parameters
//check if player exists in hash
//remove players from group's dss
//check if is in by score and by level and if not decrease num of not included
//remove player from system's dss
StatusType PlayersManager::RemovePlayer(int PlayerID)
{
    if (PlayerID <= 0)
        return INVALID_INPUT;
    Player* player = this->players_by_id->GetMember(PlayerID);
    if (player) {
        Group* group = this->groups->get_union(player->getGroupId());
        DoubleKey players_double_by_score(player->getScore(), player->getId());
        DoubleKey players_double_by_level(player->getLevel(), player->getId());
        group->removePlayer(PlayerID);
        if (this->players_by_level->find_object(players_double_by_level)) {
            this->players_by_score[player->getScore() - 1]->delete_object(&players_double_by_score);
            this->players_by_level->delete_object(&players_double_by_level);
        }
        else
            this->number_of_not_included--;
        return SUCCESS;
    }
    return FAILURE;

}

void PlayersManager::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease)
{

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
        DoubleKey players_double_by_old_score(old_score, player->getId());
        DoubleKey* players_double_by_new_score = new DoubleKey(player->getScore(), player->getId());
        DoubleKey* players_double_by_level = new DoubleKey(player->getLevel(), player->getId());
        if (!this->players_by_score[old_score]->find_object(PlayerID)) {
            this->players_by_score[old_score]->add_object(player, players_double_by_new_score);
            this->players_by_level->add_object(player, players_double_by_level);
            this->number_of_not_included--;
        }
        else {
            this->players_by_score[old_score]->delete_object(&players_double_by_score);
            this->players_by_score[NewScore]->add_object(player, players_double_by_new_score);
        }
        return SUCCESS;
    }
    return FAILURE;
}

void PlayersManager::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,double * players)
{

}

//valid parameters
//if groupid > 0 find group
//find sum of highest m and divide by m
StatusType PlayersManager::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level)
{
    if (GroupID < 0 || GroupID > this->num_of_groups || m <= 0)
        return INVALID_INPUT;
    if (GroupID > 0) {
        Group *group = this->groups->get_union(GroupID);
        AVLtree<Player, DoubleKey>* players = group->getPlayers();
        if (players->get_size() >= m)
        {
            return players->getMSum(m) / m;
        }
        return FAILURE;
    }
    else
    {
        if (this->players_by_level->getsize() >= m)
        {
            return players->getMSum(m) / m;
        }
        return FAILURE;
    }
    return SUCCESS;
}

//BONUS
void PlayersManager::GetPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers, int * HigherBoundPlayers)
{

}

~PlayersManager(){

}
