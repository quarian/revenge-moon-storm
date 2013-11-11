#include "tests.hh"

#include <cmath>
#include <cassert>

bool MapTest1(std::ostream& os) {
    os << "UNIT TEST: class Map" << std::endl;

    Map map;
    map.loadFromFile("map.txt");


    /* SECTION 1 */
    os << "TEST 1: Directional getting...";

    assert (map.getBlock(2,2)->getBlock(Direction::NORTH) == map.getBlock(2,1));
    assert (map.getBlock(2,2)->getBlock(Direction::EAST) == map.getBlock(3,2));
    assert (map.getBlock(2,2)->getBlock(Direction::SOUTH) == map.getBlock(2,3));
    assert (map.getBlock(2,2)->getBlock(Direction::WEST) == map.getBlock(1,2));

    assert (map.getBlock(9,9)->getBlock(Direction::NORTH) == map.getBlock(9,8));
    assert (map.getBlock(9,9)->getBlock(Direction::EAST) == map.getBlock(10,9));
    assert (map.getBlock(9,9)->getBlock(Direction::SOUTH) == map.getBlock(9,10));
    assert (map.getBlock(9,9)->getBlock(Direction::WEST) == map.getBlock(8,9));

    os << " OK" << std::endl;

    return true;
}
