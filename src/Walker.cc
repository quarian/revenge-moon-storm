#include "Walker.hh"
#include <cmath>

Walker::Walker(Map& map, MapBlock* location, float speed) :
        map_(map),
        location_(location), dir_(Direction::NORTH),
        target_(nullptr),
        entering_(false),
        walking_(false),
        speed_(speed),
        dx_(0.0f), dy_(0.0f) {}

void Walker::setDirection(Direction dir) {
    if (dir == dir_) return; // If already going in given direction, ignore
    if (!entering_) center(); // If exiting but changing direction, center
    dir_ = dir;
}

void Walker::updateLocation(float dt) {
    if (centered()) {
        if (!walking_) return;
        if (target_ == nullptr) knock(dt);
        else depart(dt);
    }
    else if (entering_) approach(dt);
    else depart(dt);
}

void Walker::approach(float dt) {
    float timeToCenter = (abs(dx_) + abs(dy_)) / speed_;

    if (dt >= timeToCenter) {
        center();
        update(dt - timeToCenter);
    } else {
        float distanceTraveled = dt * speed_;

        /* The fmin and fmax are here to prevent overshooting due to rounding
         * errors in the calling function. */
        if (dx_ < 0) dx_ = fmin(0.0, dx_ + distanceTraveled);
        else if (dx_ > 0) dx_ = fmax(0.0, dx_ - distanceTraveled);
        else if (dy_ < 0) dy_ = fmin(0.0, dy_ + distanceTraveled);
        else if (dy_ > 0) dy_ = fmax(0.0, dy_ - distanceTraveled);
    }
}

void Walker::depart(float dt) {
    float timeToEdge = fdim(0.5, abs(dx_) + abs(dy_)) / speed_;

    if (dt >= timeToEdge) {
        proceed();
        update(dt - timeToEdge);
    } else {
        float distanceTraveled = dt * speed_;

        /* The fmin and fmax are here to prevent overshooting due to rounding
         * errors in the calling function. */
        if (dx_ > 0) dx_ = fmin(0.5, dx_ + distanceTraveled);
        else if (dx_ < 0) dx_ = fmax(-0.5, dx_ - distanceTraveled);
        else if (dy_ > 0) dy_ = fmin(0.5, dy_ + distanceTraveled);
        else if (dy_ < 0) dy_ = fmax(-0.5, dy_ - distanceTraveled);
    }
}

void Walker::center() {
    dx_ = 0.0;
    dy_ = 0.0;
    entering_ = false;
}

void Walker::proceed() {
/*
    if (target_.isBlocked()) {
        center();
        knock();
    } else {
        map.moveTo(self, target_);
        location_ = target_;
        target_ = nullptr;

        entering_ = true;
        if (dx_ < 0) dx_ = 0.5;
        else if (dx_ > 0) dx_ = -0.5;
        else if (dy_ < 0) dy_ = 0.5;
        else if (dy_ > 0) dy_ = -0.5;
    }
*/
}

void Walker::knock(float dt=0.0) {
/*
    target_ = map.getBlock(location_, dir_);
    if (target_ == nullptr) return;
    if (target_.isBlocked()) return;
    else update(dt);
*/
}
