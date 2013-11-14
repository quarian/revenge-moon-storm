#include "tests.hh"

#include <cmath>
#include <cassert>

bool PlayerTest1(std::ostream& os) {
    os << "UNIT TEST: class Player" << std::endl;

    Map map;
    map.loadFromFile("map.txt");

    /* SECTION 0 */
    os << "TEST 0: Initialization...";

    Player deirdre("Deirdre", 3);
    // assert (deirdre.name_ == "Deirdre");
    // assert (deirdre.getLives() == 3);

    os << " OK" << std::endl;

    return true;
}
