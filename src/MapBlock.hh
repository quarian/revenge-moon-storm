#ifndef MB2_MAPBLOCK_HH
#define MB2_MAPBLOCK_HH

#include <string>
#include <vector>
#include <set>
#include <algorithm> // for find_if
#include <functional>
#include <SFML/Graphics.hpp>

#include "Map.hh"
#include "Inventory.hh"
#include "Terrain.hh"
#include "Direction.hh"

// Forward declaration
class Walker;
class Map;
class Item;
class Inventory;
class Actor;
class ControlledActor;

class MapBlock {
    public:
        MapBlock(int x, int y, char content, Map& map, Terrain terrain);
        ~MapBlock() {};
        MapBlock(const MapBlock& other);
        MapBlock operator=(const MapBlock& other);

        int x_;
        int y_;
        bool visible_;

        /* Functions for simple maths related to block-block relationships.
         * getSquareDistance returns the distance squared r^2, getManhattanDistance
         * returns the Manhattan distance (|dx| + |dy|), and getFacingTo returns
         * the (approximate) direction from this block to the target (or NULLDIR
         * if they're the same).
         */
        int getSquareDistance(MapBlock const*) const;
        int getManhattanDistance(MapBlock const*) const;
        Direction getFacingTo(MapBlock const*) const;

        char content_;
        bool isPassable() const;
        bool isDiggable() const;

        MapBlock* getBlock(Direction direction) const;
        MapBlock* getRandomPassableNeighbor() const;
        MapBlock* getRandomNeighbor(std::function<bool(MapBlock*)>) const;

        Map& getMap() const { return map_; }
        void exit(Walker* w);
        void enter(Walker* w);

        void pushItem(Item* item) { items_.insert(item); }
        void popItem(Item* item) { items_.erase(item); }

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
        Terrain& getTerrain() { return terrain_; }

        sf::Texture const& getTexture() const { return terrain_.type->texture; }

        std::vector<ControlledActor*> getPlayers();
        

    private:
        std::set<Walker*> walkers_;
        std::set<Item*> items_;
        Map& map_;
        Terrain terrain_;
};

#endif
