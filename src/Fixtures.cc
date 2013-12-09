#include "Fixtures.hh"
#include "Player.hh"
#include "Actor.hh"

Fixtures::LevelExit::LevelExit(
        Map& map,
        MapBlock* mb,
        bool& flagVictory,
        std::vector<Player*> players
    ) :
        Item(map, mb, "Level Exit", true, false, Direction::NULLDIR),
        flagVictory_(flagVictory),
        players_(players),
        exiter_(nullptr)
    {
}


void Fixtures::LevelExit::update(float) {
    for (auto p : players_) {
        auto a = p->getActor();
        if (a && a->getLocation() == location_) {
            flagVictory_ = true;
            exiter_ = p;
            break;
        }
    }
}
