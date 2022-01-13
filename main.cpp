

#include <iostream>
#include "HashTable.h"
#include "Group.h"
#include "PlayersManager.h"
#include "DoubleKey.h"

int main(){
	PlayersManager* a= new PlayersManager(5,7);
	a->AddPlayer(1,1,1);
	a->AddPlayer(2,4,3);
	a->AddPlayer(3,2,5);
	a->AddPlayer(4,3,7);
	a->AddPlayer(12,3,3);
	a->AddPlayer(5,5,8); //
	a->AddPlayer(6,5,6);
	a->AddPlayer(6,3, 4); //
	a->AddPlayer(8,1,2);
	a->AddPlayer(9,2,9); //
	a->AddPlayer(-7,4,4); //
	a->IncreasePlayerIDLevel(1, 2);
	double x;
	a->IncreasePlayerIDLevel(2,1);
	a->IncreasePlayerIDLevel(4,2);
	a->IncreasePlayerIDLevel(12,8);
	a->GetPercentOfPlayersWithScoreInBounds(1, 1, 0, 3, &x);
	a->MergeGroups(1,2);
    a->AverageHighestPlayerLevelByGroup(0, 4, &x);
    a->AverageHighestPlayerLevelByGroup(3, 2, &x);
	delete a;
}
