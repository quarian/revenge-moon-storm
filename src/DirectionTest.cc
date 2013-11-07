#include "Direction.hh"

#include <cassert>
#include <iostream>

bool DirectionTest() {
    /* Self equality test */
    assert (Direction::NORTH == Direction::NORTH);
    assert (Direction::EAST == Direction::EAST);
    assert (Direction::SOUTH == Direction::SOUTH);
    assert (Direction::WEST == Direction::WEST);

    /* Distinction test */
    assert (Direction::NORTH != Direction::EAST);
    assert (Direction::NORTH != Direction::SOUTH);
    assert (Direction::NORTH != Direction::WEST);
    assert (Direction::EAST != Direction::SOUTH);
    assert (Direction::EAST != Direction::WEST);
    assert (Direction::SOUTH != Direction::WEST);

    /* Negation test */
    assert (-Direction::NORTH == Direction::SOUTH);
    assert (-Direction::EAST == Direction::WEST);
    assert (-Direction::SOUTH == Direction::NORTH);
    assert (-Direction::WEST == Direction::EAST);

    return true;
}
