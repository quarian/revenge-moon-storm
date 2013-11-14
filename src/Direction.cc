#include "Direction.hh"

Direction Direction::in(float distance) const {
    float x2 = 0.0;
    float y2 = 0.0;
    if (x_ < 0) x2 = fmin(0.0, x_ + distance);
    else if (x_ > 0) x2 = fmax(0.0, x_ - distance);
    else if (y_ < 0) y2 = fmin(0.0, y_ + distance);
    else if (y_ > 0) y2 = fmax(0.0, y_ - distance);
    return Direction(x2, y2);
}
    

Direction Direction::out(float distance, Direction dir) const {
    float x2 = 0.0;
    float y2 = 0.0;
    if (dir == Direction::NORTH) y2 = fmax(-0.5, y_ - distance);
    else if (dir == Direction::EAST) x2 = fmin(0.5, x_ + distance);
    else if (dir == Direction::SOUTH) y2 = fmin(0.5, y_ + distance);
    else if (dir == Direction::WEST) x2 = fmax(-0.5, x_ - distance);
    return Direction(x2, y2);
}


bool Direction::eq(float x2, float y2) const {
    static const float EPSILON = 0.000001;
    if (fdim(x_, x2) > EPSILON) return false;
    if (fdim(y_, y2) > EPSILON) return false;
    return true;
}


const Direction Direction::NULLDIR = Direction(0, 0);

const Direction Direction::NORTH = Direction(0, -1);
const Direction Direction::EAST = Direction(1, 0);
const Direction Direction::SOUTH = Direction(0, 1);
const Direction Direction::WEST = Direction(-1, 0);


std::ostream& operator<<(std::ostream& os, Direction const& dir) {
    return os << "Direction(" << dir.x() << ", " << dir.y() << ")";
}
