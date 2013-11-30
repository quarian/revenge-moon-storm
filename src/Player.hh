#ifndef MB2_PLAYER_HH
#define MB2_PLAYER_HH

#include "ControlledActor.hh"
#include "Direction.hh"
#include "Inventory.hh"

#include <string>

class Player {
friend bool PlayerTest1(std::ostream&);

public:
    /* Constructor. */
    Player(std::string, size_t=1);
    ~Player();

    /* Spawns a new Actor onto the given map.
     *
     * This function assumes that the MapBlock can accommodate the Actor. */
    ControlledActor* spawn(Map&, MapBlock*);

    /* Kills the avatar. */
    void die();
    
    /* Passes commands to the Actor. */
    void keyUp(Direction);
    void keyDown(Direction);
    void changeWeapon();
    void useItem();

    /* Getters */
    size_t getLives() const { return lives_; }
    std::string getName() const { return name_; }
    std::string getCurrentItem() const { return currentItem_; }

    void setLives(size_t lives) { lives_ = lives; }
    ControlledActor* getActor() { return avatar_; }

protected:
    float speed_;
    float digPower_;
    float resistance_;
    size_t lives_;

    std::string name_;

    Inventory inventory_;
    std::string currentItem_;
    ControlledActor* avatar_;

    /* Make sure that no avatar is connected; delete it if it is. */
    bool clearAvatar();
};

#endif
