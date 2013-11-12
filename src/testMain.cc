/* Test suite -- a series of functions that assert different behaviors of
 * system components. */
#include "tests.hh"

#include <iostream>

int main() {
    std::cout << "DirectionTest" << std::endl;
    //DirectionTest();
    std::cout << std::endl;

    std::cout << "WalkerTest1" << std::endl;
    //WalkerTest1();
    std::cout << std::endl;

    std::cout << "ActorTest1" << std::endl;
    ActorTest1();
    std::cout << std::endl;

    std::cout << "ControlledActorTest1" << std::endl;
    //ControlledActorTest1();
    std::cout << std::endl;

    std::cout << "PlayerTest1" << std::endl;
    PlayerTest1();
    std::cout << std::endl;

    std::cout << "MapTest1" << std::endl;
    //MapTest1();
    std::cout << std::endl;

    std::cout << "InventoryTest1" << std::endl;
    InventoryTest1();
}

