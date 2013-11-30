#ifndef MB2_DIRECTION_HH
#define MB2_DIRECTION_HH

#include <cmath>
#include <cassert>
#include <iostream>

/* Direction
 *
 * Objects of this class essentially specify points on the x-axis or y-axis
 * (which can be used to signify an offset from the center of a MapBlock).
 * Unit Directions are provided for the four main directions.
 */
class Direction {
protected:
    float x_, y_;

public:
    /* Constructor. */
    Direction(float x, float y) : x_(x), y_(y) { }

    float x() const { return x_; }
    float y() const { return y_; }

    /* Returns the angle of this direction in degrees, so that EAST is 0
     * degrees, SOUTH is 90, and so on. If the direction is zero, returns
     * UNDEFINED_ANGLE.
     */
    float angle() const;
    static constexpr float UNDEFINED_ANGLE = 1000.0f;
        

    /* Returns how far this is from 0.0 */
    float length() const { return fabs(x_) + fabs(y_); }

    bool operator==(Direction const& other) const { return (other.x_ == x_) && (other.y_ == y_); }
    bool operator!=(Direction const& other) const { return !(*this == other); }
    bool operator<(Direction const& other) const; // For std::map
    Direction operator-() const { return Direction(-x_, -y_); }
    Direction operator*(float mul) const { return Direction(mul*x_, mul*y_); }

    /* Moves the direction vector closer to the center.
     * Never overshoots the origin 0.0. */
    Direction in(float) const;
        
    /* Moves the direction vector closer to the edge in the given direction.
     * Never overshoots +/- 0.5 on any edge. */
    Direction out(float, Direction) const;

    /* Returns whether the given Direction is "approximately" equal to this
     * one, that is whether it is within some EPSILON of it. */
    bool eq(float, float) const;
        

    static const Direction NULLDIR;
    
    static const Direction NORTH;
    static const Direction EAST;
    static const Direction SOUTH;
    static const Direction WEST;
};

std::ostream& operator<<(std::ostream&, Direction const&);

#endif
