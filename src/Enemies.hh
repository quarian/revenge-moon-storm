#ifndef MB2_ENEMIES_HH
#define MB2_ENEMIES_HH

#include <SFML/Graphics.hpp>
#include "AIPlayerSeeker.hh"
#include "GraphicsManager.hh"
#include "Game.hh"
#include "Map.hh"

class Actor;

/* Tiny Bug
 *
 * Agile little pests with low damage and health. */
class TinyBug : public AIPlayerSeeker {
public:
    TinyBug(Map&, MapBlock*);
    void splatter();
};


class GreenBug : public AIPlayerSeeker {
public:
    GreenBug(Map&, MapBlock*);
    void splatter();
};


class Lurker : public AIPlayerSeeker {
public:
    Lurker(Map&, MapBlock*);
    void splatter();
};


class Scarab : public AIPlayerSeeker {
public:
    Scarab(Map&, MapBlock*, Actor*, float=10.0, float=1.2, int=20);
    void splatter();
    void think();
    void update(float);
    bool takeDamage(float);
private:
    float fuse_;
    int power_;
    Actor* target_;
    void explode();
};


class ScarabQueen : public AIPlayerSeeker {
public:
    ScarabQueen(Map&, MapBlock*);
    void splatter();
    void think();
    void update(float);
private:
    std::vector<float> scarabs_; // Scarab state
    float launchCooldown_; // Time since last scarab was launched
    int scarabsReady(); // How many scarabs are ready?
    bool launchScarabAtNearest(std::vector<std::pair<float, Actor*>>);
    void launchScarab(Actor*);
};


#endif
