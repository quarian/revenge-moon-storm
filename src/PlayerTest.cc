#include "tests.hh"

#include <cmath>
#include <cassert>

bool PlayerTest1(std::ostream& os) {
    os << "UNIT TEST: class Player" << std::endl;

    Map map;
    Map& map_ref = map;
    map.loadFromFile("map.txt");

    /* SECTION 0 */
    os << "TEST 0: Initialization...";

    Player deirdre("Deirdre", 3);
    assert (deirdre.getName() == "Deirdre");
    assert (deirdre.getLives() == 3);
    assert (deirdre.name_  == "Deirdre");
    assert (deirdre.lives_ == 3);

    os << " OK" << std::endl;

    /* SECTION 1 */
    os << "TEST 1: Spawning and clearing the avatar...";

    assert (deirdre.avatar_ == nullptr);
    deirdre.spawn(map_ref, map.getBlock(1,1));
    assert (deirdre.avatar_ != nullptr);
    deirdre.clearAvatar();
    assert (deirdre.avatar_ == nullptr);

    os << " OK" << std::endl;

    return true;
}
