#ifndef MB2_DIRECTION_HH
#define MB2_DIRECTION_HH

#include <utility>

class Direction {
public:
    float x_, y_;

    Direction(float x, float y) : x_(x), y_(y) {}

    bool operator==(Direction const& other) const { return (other.x_ == x_) && (other.y_ == y_); }
    bool operator!=(Direction const& other) const { return !(*this == other); }
    Direction operator-() const { return Direction(-x_, -y_); }
    std::pair<int, int> toXY() { return std::make_pair(x_, y_); }

    static const Direction NORTH;
    static const Direction EAST;
    static const Direction SOUTH;
    static const Direction WEST;
};


#endif
