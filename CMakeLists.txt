cmake_minimum_required(VERSION 2.8.12.2)
project(Wet2_DS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -DNDEBUG -Wall")

add_executable(Wet2_DS main.cpp Group.h PlayersManager.cpp Group.cpp Player.cpp DoubleKey.cpp Player.h DoubleKey.h UnionFind.h UnionNode.h HashTableNode.h HashTable.h library2.h PlayersManager.h)
