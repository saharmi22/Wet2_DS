

#include <iostream>
#include "HashTable.h"
#include "Group.h"
#include "PlayersManager.h"
#include "DoubleKey.h"

int main()
{
PlayersManager* a= new PlayersManager(4,3);
a->AddPlayer(1,1,1);
a->IncreasePlayerIDLevel(1, 1);
double x;
int i = a->GetPercentOfPlayersWithScoreInBounds(1, 1, 0, 3, &x);
delete a;
}
