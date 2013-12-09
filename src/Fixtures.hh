#ifndef MB2_FIXTURES_HH
#define MB2_FIXTURES_HH

#include "Item.hh"
#include <vector>
class Player;

namespace Fixtures {
    class LevelExit : public Item {
    public:
        LevelExit(Map&, MapBlock*, bool&, std::vector<Player*>);
        bool takeDamage(int) { return false; }
        void update(float);
        Player* getExiter() const { return exiter_; }

    private:
        bool& flagVictory_; // Set this flag if someone reaches the exit
        std::vector<Player*> players_; // Who can reach the exit
        Player* exiter_; // Which player succeeded in exiting
    };
}

#endif
