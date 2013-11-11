#include "tests.hh"

#include <cmath>
#include <cassert>

bool PlayerTest1(std::ostream& os) {
    os << "UNIT TEST: class Actor" << std::endl;

    Map map;
    map.loadFromFile("map.txt");
    /*
        speed: 2.0
        digging power: 3.0
        health: 120
        resistance: 10%
    */
    Actor a(map, map.getBlock(1,1), 2.0f, 3.0f, 120, 0.1);

    /* SECTION 0
    os << "TEST 0: Initialization...";

    os << " OK" << std::endl;
    */

    return true;
}
