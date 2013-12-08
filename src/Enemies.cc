#include "Enemies.hh"

TinyBug::TinyBug(Map& map, MapBlock* mb) :
        AIPlayerSeeker(map, mb, 5, 10.0, 15, 12) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("tiny_bug"), sf::Color::Red);
    sprite_.setFrameTime(sf::seconds(0.07f));
}

void TinyBug::splatter() { new BugSplat(map_, location_); }



GreenBug::GreenBug(Map& map, MapBlock* mb) :
        AIPlayerSeeker(map, mb, 15, 7.0, 45, 17) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("medium_bug"), sf::Color::Green);
    sprite_.setFrameTime(sf::seconds(0.10f));
}

void GreenBug::splatter() { new BigBugSplat(map_, location_); }
