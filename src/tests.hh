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

bool DirectionTest();

bool WalkerTest1(std::ostream& os=std::cout);
bool ActorTest1(std::ostream& os=std::cout);
bool ControlledActorTest1(std::ostream& os=std::cout);
bool PlayerTest1(std::ostream& os=std::cout);

bool MapTest1(std::ostream& os=std::cout);

#endif
