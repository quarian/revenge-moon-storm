#include <deque>
#include <cmath>

#include "Enemies.hh"
#include "AStar.hh"
#include "Item.hh"

/*
     ****************
     * CONSTRUCTORS *
     ****************
*/

TinyBug::TinyBug(Map& map, MapBlock* mb) :
        AIPlayerSeeker(map, mb, 10, 7.0, 15, 12) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("tiny_bug"), sf::Color::Yellow);
    sprite_.setFrameTime(sf::seconds(0.07f));
}


GreenBug::GreenBug(Map& map, MapBlock* mb) :
        AIPlayerSeeker(map, mb, 20, 4.5, 45, 15) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("medium_bug"), sf::Color::Green);
    sprite_.setFrameTime(sf::seconds(0.10f));
}


Lurker::Lurker(Map& map, MapBlock* mb) :
        AIPlayerSeeker(map, mb, 40, 5.2, 120, 20) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("zombie"), sf::Color::Green);
    sprite_.setFrameTime(sf::seconds(0.10f));
}


Scarab::Scarab(Map& map,
               MapBlock* mb,
               Actor* tgt,
               float speed,
               float fuse,
               int power) :
        AIPlayerSeeker(map, mb, 0, speed, 1, 1),
        fuse_(fuse),
        power_(power),
        target_(tgt) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("scarab"), sf::Color::Red);
    sprite_.setFrameTime(sf::seconds(0.03f));
}


ScarabQueen::ScarabQueen(Map& map, MapBlock* mb, float dps, float speed, int health, int los) :
        AIPlayerSeeker(map, mb, dps, speed, health, los),
        scarabs_({0, 0, 0}),
        launchCooldown_(0) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("queen"), sf::Color::Magenta);
    sprite_.setFrameTime(sf::seconds(0.10f));
}



MoonKing::MoonKing(Map& map, MapBlock* mb, bool& flagVictory) :
        ScarabQueen(map, mb, 50, 2.4, 500, 20), flagVictory_(flagVictory) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("boss"), sf::Color::Red);
    sprite_.setFrameTime(sf::seconds(0.20f));
}



/*
     *********
     * LOGIC *
     *********
*/



void Scarab::think() {
    auto path = AStar::find(location_,
                            target_->getLocation(),
                            AStar::SimpleCostFunction(),
                            false);
    if (path.empty()) wander(1);
    else pushPath(path, 1);
}

void Scarab::update(float dt) {
    if (isAlive()) {
        fuse_ -= dt;
        if (fuse_ <= 0 || location_ == target_->getLocation()) explode();
        AIPlayerSeeker::update(dt);
    }
}

void Scarab::explode() {
    health_ = -100;
    map_.blast(1.5, 30, location_);
}

bool Scarab::takeDamage(float) {
    if (isAlive()) {
        explode();
    }
    return true;
}

void ScarabQueen::think() {
    if (launchCooldown_ > 0 || scarabsReady() == 0) {
        wander(1);
    } else {
        auto players = playersInRange();
        bool success = false;
        if (!players.empty())
            success = launchScarabAtNearest(players);
        if (!success) wander();
    }
}

bool ScarabQueen::launchScarabAtNearest(
            std::vector<std::pair<float, Actor*>> tgts) {
    for (auto a : tgts) {
        auto path = AStar::find(location_,
                                a.second->getLocation(),
                                AStar::SimpleCostFunction(),
                                false, true, LOS_);
        if (path.empty()) continue;
        launchScarab(a.second);
        return true;
    }
    return false;
}

void ScarabQueen::launchScarab(Actor* a) {
    launchCooldown_ = 0.36;
    for (auto& s : scarabs_) {
        if (s == 0) {
            s = 5.0f;
            break;
        }
    }
    Scarab* scarab = new Scarab(map_, location_, a);
    map_.monsters.insert(scarab);
    location_->enter(scarab);
}

int ScarabQueen::scarabsReady() {
    int count = 0;
    for (auto s : scarabs_)
        if (s == 0) count++;
    return count;
}

void ScarabQueen::update(float dt) {
    if (launchCooldown_ > 0)
        launchCooldown_ = fmax(0.0, launchCooldown_ - dt);
    for (auto& s : scarabs_) {
        if (s > 0) {
            s = fmax(0.0, s - dt);
        }
    }
    AIPlayerSeeker::update(dt);
}


bool MoonKing::takeDamage(float dmg) {
    bool res = ScarabQueen::takeDamage(dmg);
    if (!isAlive()) flagVictory_ = true;
    return res;
}


/*
     ************
     * SPLATTER *
     ************
*/

void TinyBug::splatter() { new BugSplat(map_, location_); }
void GreenBug::splatter() { new BigBugSplat(map_, location_); }
void Lurker::splatter() { new ZombieSplat(map_, location_); }
void Scarab::splatter() { /* No splatter, just an explosion */ }
void ScarabQueen::splatter() { new QueenSplat(map_, location_); }
void MoonKing::splatter() { new BigBugSplat(map_, location_); }
