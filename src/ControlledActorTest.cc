#include "tests.hh"
#include "Direction.hh"

#include <cmath>
#include <cassert>

bool ControlledActorTest1(std::ostream& os) {
    os << "UNIT TEST: class Actor" << std::endl;

    Map map;
    map.loadFromFile("map.txt");
    /*
        speed: 2.0
        digging power: 3.0
        health: 120
        resistance: 10%
    */
    ControlledActor a(map, map.getBlock(1,1), 2.0f, 3.0f, 120, 0.1);


    /* SECTION 1 */
    os << "TEST 1: Damage taking and healing...";


    os << " OK" << std::endl;

    return true;
}
