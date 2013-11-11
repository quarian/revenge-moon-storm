#include "ControlledActor.hh"

#include <iostream>

ControlledActor::ControlledActor(
    Map& map,
    MapBlock* block,
    float speed,
    float digPower,
    int health=100,
    float resistance=0.0) :
        Actor(map, block, speed, digPower, health, resistance),
        northKeyDown_(false),
        eastKeyDown_(false),
        southKeyDown_(false),
        westKeyDown_(false),
        orders_(Direction::NULLDIR) { }


void ControlledActor::findTarget(float dt) {
    if (orders_ != Direction::NULLDIR) {
        knock(orders_);
        if (target_) update(dt);
    }
}


void ControlledActor::keyDown(Direction dir) {
    setKey(dir, true);
    if (dir == -orders_) reverse();
    orders_ = dir;
}


void ControlledActor::keyUp(Direction dir) {
    setKey(dir, false);
    if (orders_ == dir) { // Current direction undone -- check others
        orders_ = Direction::NULLDIR;
        if (northKeyDown_) orders_ = Direction::NORTH;
        else if (eastKeyDown_) orders_ = Direction::EAST;
        else if (southKeyDown_) orders_ = Direction::SOUTH;
        else if (westKeyDown_) orders_ = Direction::WEST;
    }
}


void ControlledActor::setKey(Direction dir, bool state) {
    if (dir == Direction::NORTH) northKeyDown_ = state;
    else if (dir == Direction::EAST) eastKeyDown_ = state;
    else if (dir == Direction::SOUTH) southKeyDown_ = state;
    else if (dir == Direction::WEST) westKeyDown_ = state;
} 
