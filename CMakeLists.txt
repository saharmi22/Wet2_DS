cmake_minimum_required(VERSION 2.8.12.2)
project(Wet2_DS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -DNDEBUG -Wall")

add_executable(Wet2_DS main.cpp HashTable.h HashTable.cpp AvlTree.h HashTableNode.cpp HashTableNode.h UnionNode.h UnionFind.cpp UnionNode.cpp UnionFind.h Player.cpp Player.h Group.cpp Group.h PlayersManager.cpp PlayersManager.h)
