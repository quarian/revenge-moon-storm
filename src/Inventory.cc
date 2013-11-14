#include "Inventory.hh"
#include "Item.hh"

Inventory::Inventory() {
	//Initializes the inventory map to 0 for each item string
	for (auto i : Item::names()) {
		items_[i] = 0;
	}
	gold_ = 0;
}
Inventory::~Inventory() {}

std::map<std::string, size_t> Inventory::getNonzeroItems() {
	std::map<std::string, size_t> r_items;
	for (auto i : items_) {
		if (i.second != 0) {
			r_items[i.first] = i.second;
		}
	}
	return r_items;
}

size_t Inventory::getItemCount(std::string item) const {
	return items_[item];
}

bool Inventory::decreaseGold(int amount) {
	if (gold_ < amount) return false;
	gold_ -= amount;
	return true;
}

void Inventory::increaseGold(int amount) {
	gold_ += amount;
}

void Inventory::addItem(std::string item) {
	items_[item] += 1;
}

bool Inventory::useItem(std::string item, Map& map, MapBlock* mb) {
	if (items_[item] > 0) {
		items_[item] -= 1;

		Item* new_item = NULL;
		if (item == "Small Bomb") {
			new_item = new SmallBomb(map, mb);
		}

		//map.getGame().pushItem(new_item);
		//mb->pushItem(new_item);

		return true;
	}
	return false;
}

void Inventory::collect(Item* item) {
	if (Treasure* t = dynamic_cast<Treasure*>(item)) {
		increaseGold(t->getWorth());

		//the item's constructor informs all the other holders of this data that its being deleted.
		delete item;
	}
}