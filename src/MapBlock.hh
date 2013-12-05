#ifndef MB2_MAPBLOCK_HH
#define MB2_MAPBLOCK_HH

#include <string>
#include <vector>
#include <set>
#include <algorithm> // for find_if
#include <SFML/Graphics.hpp>

#include "Map.hh"
#include "Inventory.hh"
#include "Terrain.hh"

// Forward declaration
class Walker;
class Map;
class Item;
class Inventory;
class Actor;

class MapBlock {
    public:
        MapBlock(int x, int y, std::string content, Map& map, Terrain terrain);
        ~MapBlock() {};
        MapBlock(const MapBlock& other);
        MapBlock operator=(const MapBlock& other);

        int x_;
        int y_;
        std::string content_;
        bool isPassable() const;
        bool isDiggable() const;
        MapBlock* getBlock(Direction direction) const;
        Map& getMap() const { return map_; }
        void exit(Walker* w);
        void enter(Walker* w);
        void pushItem(Item* item);
        void popItem(Item* item);
        void collect(Inventory* inventory);
        
        /* Methods related to digging.
         *
         *  clear()             completely clear (dig out) the block, unless indestructable
         *  weaken(dmg)         weaken (dig) block by the given amount
         *  takeDamage(dmg)     take damage -- weaken the block and damage items
         *  getToughness()      return the block's toughness
         */
        void clear();
        void weaken(float);
        void takeDamage(int amount);
        float getToughness() const { return terrain_.toughness; }

        sf::Texture const& getTexture() const { return terrain_.type->texture; }
        

    private:
        std::set<Walker*> walkers_;
        std::set<Item*> items_;
        Map& map_;
        Terrain terrain_;
};

#endif
