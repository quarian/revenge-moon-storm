#include <algorithm>
#include <utility>
#include <cmath>
#include <cstdlib>

#include "AIPlayerSeeker.hh"
#include "AStar.hh"
#include "Direction.hh"
#include "Player.hh"


AIPlayerSeeker::AIPlayerSeeker(
        Map& map,
        MapBlock* block,
        float dps,
        float speed,
        int health,
        int LOS) :
    AIActor(map, block, speed, 0.0, health, 0.0, nullptr),
    dps_(dps),
    LOS_(LOS),
    LOS2_(LOS*LOS),
    queuedSleep_(0.0f) {}


void AIPlayerSeeker::think() {
    cancelPath();

    auto players = playersInRange();

    bool success = false;

    /* If already in the same square as someone, stay there */
    if (!players.empty() && players[0].first == 0) {
        sleep_ = 0.1f;
        success = true;
    }

    /* Otherwise, plot a course. */
    else if (!players.empty()) {
        success = chaseNearest(players);
    }

    /* If failed to find a path to some player, wander */
    if (!success) wander();

    needThink_ = false;
}


void AIPlayerSeeker::queueSleep() {
    // Choose a sleep time
    queuedSleep_ = exp(0.003 * (rand() % 100)) - 1;
}


int AIPlayerSeeker::planPathLength(float dist) const {
    return floor(log2(dist) / 2) + 2;
}


bool AIPlayerSeeker::chaseNearest(
            std::vector<std::pair<float, Actor*>> tgts,
            bool limited) {
    for (auto a : tgts) {
        auto path = AStar::find(location_,
                                a.second->getLocation(),
                                AStar::SimpleCostFunction(),
                                false, true, LOS_);
        if (path.empty()) continue;
        int plotlen = limited ? planPathLength(a.first) : -1;
        pushPath(path, plotlen);
        return true;
    }
    return false;
}


void AIPlayerSeeker::wander(int distance) {
    if (queuedSleep_ > 0) {
        sleep_ = queuedSleep_;
        queuedSleep_ = 0;
    } else {
        pushPath(map_.randomDestinationWalk(location_, distance));
        queueSleep();
    }
}


void AIPlayerSeeker::update(float dt) {
    auto targets = location_->getPlayers();
    for (auto p : targets) {
        p->takeDamage(dps_ * dt);
    }
    AIActor::update(dt);
}


std::vector<std::pair<float, Actor*>> AIPlayerSeeker::playersInRange(float range2) {
    range2 = (range2 != -1) ? range2 : LOS2_;
    std::vector<std::pair<float, Actor*>> players;
    for (auto p : map_.players) {
        int r2 = p->getActor()->getLocation()->getSquareDistance(location_);
        if (r2 <= range2) players.push_back({ r2, p->getActor() });
    }
    std::sort(players.begin(), players.end());
    return players;
}
