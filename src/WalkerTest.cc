#include "tests.hh"
#include "Direction.hh"

#include <cmath>
#include <cassert>

bool WalkerTest1(std::ostream& os) {
    os << "UNIT TEST: class Walker" << std::endl;

    Map map;
    map.loadFromFile("map.txt");
    Walker w(map, map.getBlock(1,1), 2.0f);

    /* SECTION 0 */
    os << "TEST 0: Initialization...";
    /* Initialization */

    assert (w.dPos_ == Direction::NULLDIR);
    assert (w.location_ == map.getBlock(1,1));
    assert (w.target_ == nullptr);

    os << " OK" << std::endl;

    /* SECTION 1 */
    os << "TEST 1: Updating at standstill...";
    w.update(0.1);

    assert (w.dPos_ == Direction::NULLDIR);
    assert (w.location_ == map.getBlock(1,1));
    assert (w.target_ == nullptr);

    os << " OK" << std::endl;

    /* SECTION 2 */
    os << "TEST 2: Moving around in one square...";
    w.knock(Direction::EAST);

    assert (w.dPos_ == Direction::NULLDIR);
    assert (w.facing_ == Direction::EAST);
    assert (w.location_ == map.getBlock(1,1));
    assert (w.target_ == map.getBlock(2,1));

    w.update(0.1);

    assert (w.dPos_.eq(0.2, 0.0));
    assert (w.location_ == map.getBlock(1,1));
    assert (w.target_ == map.getBlock(2,1));

    w.update(0.1);

    assert (w.dPos_.eq(0.4, 0.0));
    assert (w.location_ == map.getBlock(1,1));
    assert (w.target_ == map.getBlock(2,1));

    os << " OK" << std::endl;

    /* SECTION 3 */
    os << "TEST 3: Moving to another square...";

    w.update(0.1);

    assert (w.location_ == map.getBlock(2,1));
    assert (w.target_ == map.getBlock(2,1));
    assert (w.dPos_.eq(-0.4, 0.0));

    w.update(0.3);
    assert (w.dPos_ == Direction::NULLDIR);
    assert (w.location_ == map.getBlock(2,1));
    assert (w.facing_ == Direction::EAST);
    assert (w.target_ == nullptr);

    w.update(0.3);

    assert (w.dPos_ == Direction::NULLDIR);
    assert (w.location_ == map.getBlock(2,1));
    assert (w.facing_ == Direction::EAST);
    assert (w.target_ == nullptr);

    os << " OK" << std::endl;

    /* SECTION 4 */
    os << "TEST 4: Moving several squares...";

    w.knock(Direction::SOUTH);

    assert (w.location_ == map.getBlock(2,1));
    assert (w.facing_ == Direction::SOUTH);
    assert (w.target_ == map.getBlock(2,2));
    assert (w.dPos_ == Direction::NULLDIR);

    w.update(0.2);

    assert (w.location_ == map.getBlock(2,1));
    assert (w.target_ == map.getBlock(2,2));
    assert (w.facing_ == Direction::SOUTH);
    assert (w.dPos_.eq(0.0, 0.4));

    w.update(1.3);

    assert (w.location_ == map.getBlock(2,2));
    assert (w.target_ == nullptr);
    assert (w.facing_ == Direction::SOUTH);
    assert (w.dPos_ == Direction::NULLDIR);

    w.knock(Direction::SOUTH);
    w.update(0.6);
    w.knock(Direction::EAST);
    w.update(0.6);
    w.knock(Direction::EAST);
    w.update(0.6);
    w.knock(Direction::EAST);
    w.update(0.6);
    w.knock(Direction::EAST);
    w.update(0.6);

    assert (w.dPos_ == Direction::NULLDIR);
    assert (w.location_ == map.getBlock(6,3));
    assert (w.facing_ == Direction::EAST);
    assert (w.target_ == nullptr);

    os << " OK" << std::endl;

    /* SECTION 5
    os << "TEST 5: Knocking on walls...";

    w.knock(Direction::EAST);

    assert (w.location_ == map.getBlock(6,3));
    assert (w.target_ == nullptr);
    assert (w.facing_ == Direction::EAST);
    assert (w.dPos_ == Direction::NULLDIR);
    
    w.update(0.1);

    assert (w.location_ == map.getBlock(6,3));
    assert (w.target_ == nullptr);
    assert (w.facing_ == Direction::EAST);
    assert (w.dPos_ == Direction::NULLDIR);

    w.knock(Direction::SOUTH);

    assert (w.location_ == map.getBlock(6,3));
    assert (w.target_ == nullptr);
    assert (w.facing_ == Direction::SOUTH);
    assert (w.dPos_ == Direction::NULLDIR);
    
    w.update(0.1);

    assert (w.location_ == map.getBlock(6,3));
    assert (w.target_ == nullptr);
    assert (w.facing_ == Direction::SOUTH);
    assert (w.dPos_ == Direction::NULLDIR);

    os << " OK" << std::endl; */

    return true;
}
