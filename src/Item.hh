#ifndef MB2_ITEM_HH
#define MB2_ITEM_HH

#include <vector>
#include <string>

#include "Map.hh"

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

class Map;
class MapBlock;


/*
 * Contains the asbtract base class for items and other varying properties of items
*/

class Item {
    /*
     * Abstract base class for items that exist in the game
     * These items are considered "dropped" or used, such that
     * player collision with a Treasure Item adds gold for that
     * player. Things like bombs are Items too, they are updated each 
     * frame.
    */
public:
    //the item needs information from the game, which is given as a reference to the map.
    //Now the items can check whether 
    Item(Map&, MapBlock*, std::string, bool, bool, Direction);
    virtual ~Item();

    virtual void update(float) = 0;
    virtual bool takeDamage(int) = 0;

    static std::vector<std::string> names(); //use this to access all the names of the items in the game
    static std::vector<std::string> passiveNames();
    static std::vector<std::string> allNames();
    static std::map<std::string, std::string> descriptions();

    Map& getMap() const { return map_; }
    MapBlock* getLocation() const { return location_; }
    std::string getName() const { return name_; }
    bool getPassable() const { return passable_; }
    bool getCollectible() const { return collectible_; }
    bool getAlive() const { return alive_; }
    Direction getDirection() const { return direction_; }
    bool isTrap() const { return trap_; }

    AnimatedSprite& getSprite() { return sprite_; }

protected:
    void buildSprite(int, std::string, float);

    Map& map_; //Reference to the map
    MapBlock* location_; //Location of the item
    std::string name_; //A name identifier for each item type
    bool passable_; //Whether the player can walk into the square this item is in.
    bool collectible_;
    bool alive_;
    Direction direction_;
    bool trap_;

    Animation anim_; //The animation, which can be set as a static, single frame animation
    AnimatedSprite sprite_; //the drawable sprite image
};

//Create treasures with
// Treasure(map reference, name of the treasure, the value of the treasure)
class Treasure : public Item {
public:
    //Takes the name of the treasure and it's worth
    Treasure(Map&, MapBlock*, std::string, int);

    void update(float);
    bool takeDamage(int) { return false; } //treasure cannot be destroyed
    int getWorth() const { return worth_; }
private:
    int worth_; //non-zero for treasures, this value is added to the player's gold reserve
};

//Abstract base class for weapons
class Weapon : public Item {
public:
    Weapon(Map& map, MapBlock* location, std::string name, bool passable, bool collectible, Direction dir = Direction::NULLDIR) : 
        Item(map, location, name, passable, collectible, dir) {};

    virtual void update(float) = 0;
    //all weapons get instantly destroyed as a consequence of an explosion or other source of damage
    virtual bool takeDamage(int) = 0;

    int getRadius() const { return radius_; }
    int getPower() const { return power_; }
    float getFusetime() const { return fusetime_; }
protected:
    int radius_;
    int power_;
    float fusetime_; //in seconds, how long the fuse will burn. Zero for instant action (e.g. guns)
};

class Weaponbox : public Item {
public:
    Weaponbox(Map&, MapBlock*);

    void update(float);
    bool takeDamage(int) { return false; }

    std::string generateItem() const;

private:
    //0.0f .. 1.0f tells what percentage of items can spawn from this crate
    //Take with a grain of salt
    
};


/*
 * Item declarations
*/
class NormalBomb : public Weapon {
public:
    NormalBomb(Map&, MapBlock*, std::string);
    void update(float);
    bool takeDamage(int);
};

class CrucifixBomb : public Weapon {
public:
    CrucifixBomb(Map&, MapBlock*, std::string);
    void update(float);
    bool takeDamage(int);
};

class Flamer : public Item {
public:
    Flamer(Map&, MapBlock*, Direction, int=10, int=15, size_t=8, float=0.03f);
    void update(float);
    bool takeDamage(int) { return false; }
private:
    int spreadChance_;
    size_t telomere_;
    int spreadSpeed_;
    int damage_;
    float lifetime_;
};

class Mine : public Weapon {
public:
    Mine(Map&, MapBlock*);
    void update(float);
    bool takeDamage(int);
    bool getArmed() const { return armed_; }
private:
    bool armed_;
};

class CarpetBomb : public Weapon {
public:
    //integer is the iteration, boolean tells if this bomb was the first (to extend the initial blast time)
    CarpetBomb(Map&, MapBlock*, int, bool);
    void update(float);
    bool takeDamage(int);
    void explode();
private:
    int iteration_;
    bool first_;
};

/*
 * Item derivates
 */
class Explosion : public Item {
public:
    Explosion(Map&, MapBlock*, float=0.3f);
    void update(float);
    bool takeDamage(int) { return false; } // I AM INVINCIBLE
private:
    float fusetime_;
};


class BloodSplatter : public Item {
public:
    BloodSplatter(Map&, MapBlock*, std::string="blood_splatter.png");
    void update(float) {}
    bool takeDamage(int) { return false; }
};

class BugSplat : public BloodSplatter {
public:
    BugSplat(Map& map, MapBlock* mb) : BloodSplatter(map, mb, "bug_splat.png") {}
};

class BigBugSplat : public BloodSplatter {
public:
    BigBugSplat(Map& map, MapBlock* mb) : BloodSplatter(map, mb, "green_bug_splat.png") {}
};

class QueenSplat : public BloodSplatter {
public:
    QueenSplat(Map& map, MapBlock* mb) : BloodSplatter(map, mb, "queen_splat.png") {}
};

class ZombieSplat : public BloodSplatter {
public:
    ZombieSplat(Map& map, MapBlock* mb) : BloodSplatter(map, mb, "zombie_splat.png") {}
};

class Dustcloud : public Item {
public:
    Dustcloud(Map&, MapBlock*);
    void update(float);
    bool takeDamage(int) { return false; }
private:
    float fusetime_;
};

class Flame : public Item {
public:
    Flame(Map&, MapBlock*);
    void update(float);
    bool takeDamage(int) { return false; }
private:
    float fusetime_;
    int anim_counter;
    int power_;
};


#endif
