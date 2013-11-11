/* Test suite -- a series of functions that assert different behaviors of
 * system components. */
#include "tests.hh"

#include <iostream>

int main() {
    DirectionTest();
    std::cout << std::endl;

    WalkerTest1();
    std::cout << std::endl;

    ActorTest1();
    std::cout << std::endl;

    ControlledActorTest1();
    std::cout << std::endl;

    MapTest1();
}

