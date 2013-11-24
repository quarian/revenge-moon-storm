#ifndef MB2_TESTS_HH
#define MB2_TESTS_HH

#include <iostream>

#include "Direction.hh"

#include "Walker.hh"
#include "Actor.hh"
#include "ControlledActor.hh"
#include "Player.hh"

#include "MapBlock.hh"
#include "Map.hh"

#include "Inventory.hh"

#include "Game.hh"

#include "AStar.hh"

bool DirectionTest();

bool WalkerTest1(std::ostream& =std::cout);
bool ActorTest1(std::ostream& =std::cout);
bool ControlledActorTest1(std::ostream& =std::cout);
bool PlayerTest1(std::ostream& =std::cout);

bool MapTest1(std::ostream& =std::cout);

bool InventoryTest1(std::ostream& =std::cout);

bool GameTest1(std::ostream& =std::cout);

bool AStarTest1(std::ostream& =std::cout);

#endif
