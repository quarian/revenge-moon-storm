#ifndef MB2_PLAYER_HH
#define MB2_PLAYER_HH

#include "ControlledActor.hh"
#include "Direction.hh"
#include "Inventory.hh"

class Player {
public:
    /* Constructor. */
    Player(size_t=1);
    ~Player() { clearAvatar(); }

    /* Spawns a new Actor onto the given map.
     *
     * This function assumes that the MapBlock can accommodate the Actor. */
    ControlledActor* spawn(Map*, MapBlock*);

    /* Kills the avatar. */
    void die();
    
    void keyUp(Direction);
    void keyDown(Direction);

    size_t getLives() const { return lives_; }
    ControlledActor* getActor() { return avatar_; }

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
