#include "Enemies.hh"

TinyBug::TinyBug(Map& map, MapBlock* mb) :
        AIPlayerSeeker(map, mb, 5, 10.0, 15, 12) {
    initSprite(map.getGame()->graphicsManager_.getAnimation("tiny_bug"), sf::Color::Red);
    sprite_.setFrameTime(sf::seconds(0.07f));
}
