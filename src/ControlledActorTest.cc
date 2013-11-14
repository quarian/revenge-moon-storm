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


    /* SECTION 0 */
    os << "TEST 0: Standing still...";

    assert (a.dPos_ == Direction::NULLDIR);
    assert (a.location_ == map.getBlock(1,1));
    assert (a.target_ == nullptr);
    a.update(10);
    assert (a.dPos_ == Direction::NULLDIR);
    assert (a.location_ == map.getBlock(1,1));
    assert (a.target_ == nullptr);

    os << " OK" << std::endl;

    /* SECTION 1 */
    os << "TEST 1: Fiddling with the keys...";

    assert (a.orders_ == Direction::NULLDIR);
    a.keyDown(Direction::NORTH);
    assert (a.orders_ == Direction::NORTH);
    a.keyUp(Direction::NORTH);
    assert (a.orders_ == Direction::NULLDIR);
    a.keyUp(Direction::NORTH);
    a.keyUp(Direction::NORTH);
    a.keyUp(Direction::NORTH);
    assert (a.orders_ == Direction::NULLDIR);
    a.keyDown(Direction::NORTH);
    a.keyDown(Direction::EAST);
    assert (a.orders_ == Direction::EAST);
    a.keyDown(Direction::WEST);
    assert (a.orders_ == Direction::WEST);
    a.keyDown(Direction::SOUTH);
    assert (a.orders_ == Direction::SOUTH);
    a.keyUp(Direction::WEST);
    assert (a.orders_ == Direction::SOUTH);
    a.keyUp(Direction::SOUTH);
    assert (a.orders_ == Direction::NORTH);
    a.keyUp(Direction::NORTH);
    assert (a.orders_ == Direction::EAST);
    a.keyUp(Direction::EAST);
    assert (a.orders_ == Direction::NULLDIR);
    a.keyDown(Direction::NORTH);

    a.keyDown(Direction::WEST);
    assert (a.orders_ == Direction::WEST);
    a.keyDown(Direction::SOUTH);
    assert (a.orders_ == Direction::SOUTH);
    a.keyUp(Direction::SOUTH);
    assert (a.orders_ == Direction::NORTH);
    a.keyUp(Direction::NORTH);
    assert (a.orders_ == Direction::WEST);
    a.keyUp(Direction::WEST);
    assert (a.orders_ == Direction::NULLDIR);

    os << " OK" << std::endl;

    /* SECTION 2 */
    os << "TEST 2: Moving forward, starting and stopping...";

    a.keyDown(Direction::SOUTH);
    a.update(0.1);
    assert (a.dPos_.eq(0.0, 0.2));
    assert (a.location_ == map.getBlock(1,1));
    assert (a.target_ == map.getBlock(1,2));
    a.update(0.1);
    assert (a.dPos_.eq(0.0, 0.4));
    assert (a.location_ == map.getBlock(1,1));
    assert (a.target_ == map.getBlock(1,2));

    a.update(0.1);
    assert (a.dPos_.eq(0.0, -0.4));
    assert (a.location_ == map.getBlock(1,2));
    assert (a.target_ == map.getBlock(1,2));

    a.update(0.4);
    assert (a.dPos_.eq(0.0, 0.4));
    assert (a.location_ == map.getBlock(1,2));
    assert (a.target_ == map.getBlock(1,3));

    a.keyUp(Direction::SOUTH);
    assert (a.dPos_.eq(0.0, 0.4));
    assert (a.location_ == map.getBlock(1,2));
    assert (a.target_ == map.getBlock(1,3));

    a.update(0.1);
    assert (a.dPos_.eq(0.0, -0.4));
    assert (a.location_ == map.getBlock(1,3));
    assert (a.target_ == map.getBlock(1,3));

    a.update(0.3);
    assert (a.dPos_ == Direction::NULLDIR);
    assert (a.location_ == map.getBlock(1,3));
    assert (a.target_ == nullptr);

    a.keyDown(Direction::SOUTH);
    a.update(0.2);
    assert (a.dPos_.eq(0.0, 0.4));
    assert (a.location_ == map.getBlock(1,3));
    assert (a.target_ == map.getBlock(1,4));

    a.update(1.1);
    assert (a.dPos_.eq(0.0, -0.4));
    assert (a.location_ == map.getBlock(1,6));
    assert (a.target_ == map.getBlock(1,6));

    a.keyUp(Direction::SOUTH);
    a.update(0.3);
    assert (a.dPos_ == Direction::NULLDIR);
    assert (a.location_ == map.getBlock(1,6));
    assert (a.target_ == nullptr);

    os << " OK" << std::endl;

    /* SECTION 3 */
    os << "TEST 3: Handling different directions and many-keys-pressed...";

    a.keyDown(Direction::NORTH);
    a.update(0.1);
    assert (a.dPos_.eq(0.0, -0.2));
    assert (a.location_ == map.getBlock(1,6));
    assert (a.target_ == map.getBlock(1,5));

    a.keyDown(Direction::EAST);
    a.update(0.1);
    assert (a.dPos_.eq(0.2, 0.0));
    assert (a.location_ == map.getBlock(1,6));
    assert (a.target_ == map.getBlock(2,6));

    a.update(3.3);
    assert (a.dPos_.eq(-0.2, 0.0));
    assert (a.location_ == map.getBlock(8,6));
    assert (a.target_ == map.getBlock(8,6));

    a.keyUp(Direction::EAST);
    a.update(0.2);
    assert (a.dPos_.eq(0.0, -0.2));
    assert (a.location_ == map.getBlock(8,6));
    assert (a.target_ == map.getBlock(8,5));

    a.update(0.8);
    assert (a.dPos_.eq(0.0, 0.2));
    assert (a.location_ == map.getBlock(8,4));
    assert (a.target_ == map.getBlock(8,4));

    a.keyUp(Direction::NORTH);
    a.update(0.4);
    assert (a.dPos_ == Direction::NULLDIR);
    assert (a.location_ == map.getBlock(8,4));
    assert (a.target_ == nullptr);

    os << " OK" << std::endl;

    return true;
}
