#ifndef MB2_INVENTORY_HH
#define MB2_INVENTORY_HH

#include <map>
#include <string>
#include "Item.hh"

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
	 * getItemCount(string)
	 * increaseGold(int)
	 *
	 * Other functions are used mainly within the Store.
	 */

	Inventory() {
		//Initializes the inventory map to 0 for each item string
		for (auto i : Item::names()) {
			items_[i] = 0;
		}
	}
	~Inventory() {}

	/* Accessors for the gold and quantity of items */
	int getGold() const { return gold_; }
	size_t getItemCount(std::string item) { return items_[item]; }

	/* Decreases the gold by the amount given, if possible, and returns a boolean */
	bool decreaseGold(int amount) {
		if (gold_ < amount) return false;
		gold_ -= amount;
		return true;
	}
	/* Increases the gold by the given amount */
	void increaseGold(int amount) {
		gold_ += amount;
	}
	/* Adds +1 to the given item's quantity */
	void addItem(std::string item) {
		items_[item] += 1;
	}
	/* Decreases the item count in the inventory, if possible, and returns a boolean */
	bool useItem(std::string item) {
		if (items_[item] > 0) {
			items_[item] -= 1;
			return true;
		}
		return false;
	}

private:
	std::map<std::string, size_t> items_;
	int gold_;
};

#endif
