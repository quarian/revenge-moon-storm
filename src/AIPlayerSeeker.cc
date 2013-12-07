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
        float damage,
        float speed,
        int health,
        int LOS) :
    AIActor(map, block, speed, 0.0, health, 0.0, nullptr),
    damage_(damage),
    LOS2_(LOS*LOS),
    queuedSleep_(0.0f) {}


void AIPlayerSeeker::think() {
    cancelPath();

    /* Get list of players within LOS, sorted by distance */
    std::vector<std::pair<float, Actor*>> players;
    for (auto p : map_.players) {
        int r2 = p->getActor()->getLocation()->getSquareDistance(location_);
        if (r2 <= LOS2_) players.push_back({ r2, p->getActor() });
    }
    std::sort(players.begin(), players.end());

    /* If already very close, plan accordingly */
    if (!players.empty() && players[0].first <= 1) {
        queueSleep();

        MapBlock* target = players[0].second->getLocation();

        if (target != location_) pushPath(target);
        MapBlock* neighbor = target->getRandomPassableNeighbor();
        if (neighbor) pushPath(neighbor);
        if (target == location_) pushPath(target);
    }
    else if (!players.empty()) {
        queueSleep();

        /* Plot a course towards the player. */
        for (auto a : players) {
            auto path = AStar::find(location_, a.second->getLocation(), AStar::SimpleCostFunction(), false);
            if (path.empty()) continue;
            int plotlen = planPathLength(a.first);
            pushPath(path, plotlen);
        }
    } else {
        if (queuedSleep_ > 0) {
            sleep_ = queuedSleep_;
            queuedSleep_ = 0;
        } else {
            pushPath(map_.randomDestinationWalk(location_, 10));
            queueSleep();
        }
    }

    needThink_ = false;
}


void AIPlayerSeeker::queueSleep() {
    // Choose a sleep time
    queuedSleep_ = exp(0.003 * (rand() % 100)) - 1;
}


int AIPlayerSeeker::planPathLength(float dist) const {
    return floor(log2(dist) / 2) + 2;
}
