#include "Fixtures.hh"
#include "Player.hh"
#include "Actor.hh"

Fixtures::LevelExit::LevelExit(
        Map& map,
        MapBlock* mb,
        bool& flagVictory,
        std::vector<Player*> players,
        std::string animation
    ) :
        Item(map, mb, "Level Exit", true, false, Direction::NULLDIR),
        flagVictory_(flagVictory),
        players_(players),
        exiter_(nullptr)
{
    if (animation == "") {
        buildSprite(4, "portal_spritesheet.png", 1);
    } else {
        buildSprite(1, animation, 0.3);
    }

    sprite_.setLooped(true);
}


void Fixtures::LevelExit::update(float dt) {
    sprite_.update(sf::seconds(dt));
    for (auto p : players_) {
        auto a = p->getActor();
        if (a && a->getLocation() == location_) {
            flagVictory_ = true;
            exiter_ = p;
            break;
        }
    }
}
