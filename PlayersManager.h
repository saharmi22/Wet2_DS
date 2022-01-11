//
// Created by sahar on 10/01/2022.
//

#ifndef WET2_DS_PLAYERSMANAGER_H
#define WET2_DS_PLAYERSMANAGER_H

#include "HashTable.h"
#include "Player.h"
#include "AvlTree.h"
#include "DoubleKey.h"
#include "UnionFind.h"
#include "library2.h"

class PlayersManager {

    HashTable<Player>* players_by_id;
    AVLtree<Player, DoubleKey>* players_by_level;
    AVLtree<Player, DoubleKey>** players_by_score;
    int number_of_not_included;
    UnionFind<Group>* groups;
    int num_of_groups;
    int scale;

public:

    PlayersManager(int k, int scale);                               //RL
    StatusType MergeGroups(int GroupID1, int GroupID2);                  //sahar
    StatusType AddPlayer(int PlayerID, int GroupID, int score);         //RL
    StatusType RemovePlayer(int PlayerID);                             //sahar
    StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);//RL
    StatusType ChangePlayerIDScore(int PlayerID, int NewScore);      //sahar
    StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,double * players);//RL
    StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level); //sahar
    StatusType GetPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers, int * HigherBoundPlayers);
    ~PlayersManager(); //RL

};


#endif //WET2_DS_PLAYERSMANAGER_H
