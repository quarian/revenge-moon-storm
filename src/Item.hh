#ifndef MB2_ITEM_HH
#define MB2_ITEM_HH

#include <vector>
#include <string>

#include "Map.hh"
#include "MapBlock.hh"

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
	 * frame with the player's current location, such that collision and
	 * damage from explosions can be calculated within the items.
	*/
public:
	//the item needs information from the game, which is given as a reference to the map.
	//Now the items can check whether 
	Item(Map& map, MapBlock* location, std::string name, bool passable) : mapref_(map), location_(location), name_(name), passable_(passable), alive_(true) {}
	virtual ~Item() {}

	virtual void update(float) = 0;
	virtual bool takeDamage(int) = 0;

	static std::vector<std::string> names(); //use this to access all the names of the items in the game
	static std::vector<std::string> treasureNames();
protected:
	Map& mapref_; //Reference to the map
	MapBlock* location_; //Location of the item
	std::string name_; //A name identifier for each item type
	bool passable_; //Whether the player can walk into the square this item is in.
	bool alive_;
};

//Create treasures with
// Treasure(map reference, name of the treasure, the value of the treasure)
class Treasure : public Item {
public:
	//Takes the name of the treasure and it's worth
	Treasure(Map&, MapBlock*, std::string, int);

	void update(float);
	bool takeDamage(int) { return false; } //treasure cannot be destroyed
private:
	int worth_; //non-zero for treasures, this value is added to the player's gold reserve
};

//Abstract base class for weapons
class Weapon : public Item {
public:
	Weapon(Map& map, MapBlock* location, std::string name, bool passable) : Item(map, location, name, passable) {}; //each weapon has to initialize their radius, power, fusetime etc.

	virtual void update(float) = 0;
	//all weapons get instantly destroyed as a consequence of an explosion or other source of damage
	virtual bool takeDamage(int) { return true; }
protected:
	int radius_;
	int power_;
	float fusetime_; //in seconds, how long the fuse will burn. Zero for instant action (e.g. guns)
};



/*
 * Item declarations
*/
class SmallBomb : public Weapon {
	SmallBomb(Map&, MapBlock*);
	void update(float);
};

#endif
