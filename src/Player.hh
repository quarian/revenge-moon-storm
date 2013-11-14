#ifndef MB2_PLAYER_HH
#define MB2_PLAYER_HH

#include "ControlledActor.hh"
#include "Direction.hh"
#include "Inventory.hh"

#include <string>

class Player {
public:
    /* Constructor. */
    Player(std::string, size_t=1);
    ~Player() { clearAvatar(); }

    /* Spawns a new Actor onto the given map.
     *
     * This function assumes that the MapBlock can accommodate the Actor. */
    ControlledActor* spawn(Map*, MapBlock*);

    /* Kills the avatar. */
    void die();
    
    /* Passes movement commands to the Actor. */
    void keyUp(Direction);
    void keyDown(Direction);

    /* Other commands:
     *
     * useItem      Tries to use the currently held item.
     */
    void useItem();

    size_t getLives() const { return lives_; }
    void setLives(size_t lives) { lives_ = lives; }
    ControlledActor* getActor() { return avatar_; }

    const std::string name_;

protected:
    float speed_;
    float digPower_;
    float resistance_;
    size_t lives_;

    Inventory inventory_;
    ControlledActor* avatar_;

    /* Make sure that no avatar is connected; delete it if it is. */
    bool clearAvatar();
};

#endif
