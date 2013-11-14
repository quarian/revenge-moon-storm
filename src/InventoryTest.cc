#include <iostream>
#include <cassert>

#include "Item.hh"
#include "Inventory.hh"
#include "tests.hh"
#include "Map.hh"
#include "MapBlock.hh"

/*
 * Contains item implementations
*/

bool InventoryTest1(std::ostream& os) {
	os << "UNIT TEST: class Inventory" << std::endl;
	Inventory inv;
	Map map;
	MapBlock* mb = new MapBlock(0,0,"", map);

	//SECTION 0
	os << "TEST 0: Initialization...";
	assert(inv.getGold() == 0);
	assert(inv.getItemCount("Small Bomb") == 0);
	assert(inv.getNonzeroItems().size() == 0);
	os << "OK" << std::endl;

	//SECTION 1
	os << "TEST 1: Adding items and gold...";
	inv.addItem("Small Bomb");
	assert(inv.getItemCount("Small Bomb") == 1);
	inv.addItem("Large Bomb");
	assert(inv.getItemCount("Large Bomb") == 1);
	inv.addItem("Small Bomb");
	assert(inv.getItemCount("Small Bomb") == 2);
	inv.increaseGold(10);
	assert(inv.getGold() == 10);
	inv.increaseGold(20);
	assert(inv.getGold() == 30);
	os << "OK" << std::endl;

	//SECTION 2
	os << "TEST 2: Using items and removing gold...";
	assert(inv.useItem("Small Bomb", map, mb));
	assert(inv.getItemCount("Small Bomb") == 1);
	assert(inv.useItem("Large Bomb", map, mb));
	assert(inv.getItemCount("Large Bomb") == 0);
	assert(inv.useItem("Large Bomb", map, mb) == false);
	assert(inv.getItemCount("Large Bomb") == 0);

	assert(inv.decreaseGold(20));
	assert(inv.decreaseGold(20) == false);
	assert(inv.getGold() == 10);
	assert(inv.decreaseGold(10));
	assert(inv.getGold() == 0);
	os << "OK" << std::endl;

	//SECTION 3
	os << "TEST 3: Confirming integrity...";
	assert(inv.getNonzeroItems().size() == 1);
	assert(inv.getGold() == 0);
	assert(inv.getItemCount("Large Bomb") == 0);
	assert(inv.getItemCount("Small Bomb") == 1);
	os << "OK" << std::endl;

	return true;
}