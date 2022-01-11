

#include <iostream>
#include "HashTable.h"
#include "Group.h"
#include "PlayersManager.h"
#include "DoubleKey.h"

int main()
{
PlayersManager* a= new PlayersManager(4,3);
a->AddPlayer(1,1,1);
delete a;
}
