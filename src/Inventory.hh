#ifndef MB2_INVENTORY_HH
#define MB2_INVENTORY_HH

#include <map>
#include <string>
#include "Item.hh"
#include "Map.hh"
#include "Direction.hh"

class Map;
class MapBlock;
class Item;
class Player;

/*
 * A simple class that handles the player's items and gold
*/

class Inventory {
public:
	/* How to use:
	 * Add an inventory object to each player in the game.
	 * When the player wants to use an item, call the
	 *
	 * useItem() 
	 *
	 * function with the item's name as parameter. It returns
	 * a boolean that indicates whether or not the player has
	 * at least one of them, and decreases the quantity. 
	 *
	 * Other relevant functions:
	 * getNonzeroItems()
	 * getItemCount(string)
	 * increaseGold(int)
	 *
	 * Other functions are used mainly within the Store.
	 */

	Inventory();
	~Inventory();

	/* Accessors for the gold and quantity of items */
	int getGold() const { return gold_; }
	void setGold(int gold) {gold_ = gold;} 
	size_t getItemCount(std::string);

	/* Returns all non-zero items in the inventory */
	std::map<std::string, size_t> getNonzeroItems();

        /* Returns the name of the first nonzero item after the given item */
        std::string getNextItem(std::string const&);

	/* Decreases the gold by the amount given, if possible, and returns a boolean */
	bool decreaseGold(int);
	/* Increases the gold by the given amount */
	void increaseGold(int);
	/* Adds +1 to the given item's quantity */
	void addItem(std::string);
	// Decreases the given item's quantity by 1. Gold is added in the caller function in Store
	void sellItem(std::string);
	/* Decreases the item count in the inventory, if possible, and returns a boolean */
	bool useItem(std::string, Map&, MapBlock*, Direction, Player*);
	//An item is picked up by an actor and given to the inventory to parse
	bool collect(Item*);
	
	int getExtraMiningPower();

private:
	std::map<std::string, size_t> items_;
	int gold_;
};


#endif
