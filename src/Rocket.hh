#ifndef MB2_ROCKET_HH
#define MB2_ROCKET_HH

#include "AIPlayerSeeker.hh"

/* This is a really shitty jury rig */
class Rocket : public AIPlayerSeeker {
public:
    Rocket(Map&, MapBlock*, Direction);
    void splatter() {}
    void think();
    void update(float);
    bool takeDamage(float);

private:
    Direction dir_;
    void explode();
};

#endif
