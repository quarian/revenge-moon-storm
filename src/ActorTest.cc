#include "tests.hh"
#include "Direction.hh"

#include <cmath>
#include <cassert>

bool ActorTest1(std::ostream& os) {
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

    /* SECTION 0 */
    os << "TEST 0: Initialization...";

    assert (!a.digging_);
    assert (a.digPower_ == 3.0);
    assert (a.health_ == 120);
    assert (a.maxHealth_ == 120);
    assert (a.vulnerability_ < 0.91);
    assert (a.vulnerability_ > 0.89);

    os << " OK" << std::endl;

    /* SECTION 1 */
    os << "TEST 1: Damage taking and healing...";

    assert (a.isAlive());

    assert (a.takeDamage(10));
    assert (a.health_ == 120 - 9);
    assert (a.isAlive());

    assert (a.takeDamage(30));
    assert (a.health_ == 120 - 9 - 27);
    assert (a.isAlive());

    assert (a.heal(10));
    assert (a.health_ == 120 - 9 - 27 + 10);
    assert (a.isAlive());

    assert (a.heal(100));
    assert (a.health_ == 120);
    assert (a.isAlive());

    assert (!a.takeDamage(200));
    assert (!a.isAlive());

    assert (!a.heal(330));
    assert (!a.isAlive());
    assert (!a.heal(330));
    assert (!a.isAlive());

    os << " OK" << std::endl;

    return true;
}
