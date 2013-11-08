#ifndef MB2_DIRECTION_HH
#define MB2_DIRECTION_HH

class Direction {
public:
    float x, y;

    Direction(float x, float y) : x(x), y(y) {}

    bool operator==(Direction const& other) const { return (other.x == x) && (other.y == y); }
    bool operator!=(Direction const& other) const { return !(*this == other); }
    Direction operator-() const { return Direction(-x, -y); }

    static const Direction NORTH;
    static const Direction EAST;
    static const Direction SOUTH;
    static const Direction WEST;
};


#endif
