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

class PlayersManager {

    HashTable<Player>* players_by_id;
    AVLtree<Player, DoubleKey>* players_by_level;
    AVLtree<Player, DoubleKey>** players_by_score;
    int number_of_not_included;
    UnionFind<Group> groups;

public:

    PlayersManager(int k, int scale);                               //RL
    void MergeGroups(int GroupID1, int GroupID2);                  //sahar
    void AddPlayer(int PlayerID, int GroupID, int score);         //RL
    void RemovePlayer(int PlayerID);                             //sahar
    void IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);//RL
    void ChangePlayerIDScore(int PlayerID, int NewScore);      //sahar
    void GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,double * players);//RL
    void AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level); //sahar
    void GetPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers, int * HigherBoundPlayers);
    ~PlayersManager(); //RL

};


#endif //WET2_DS_PLAYERSMANAGER_H
