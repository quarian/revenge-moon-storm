#include "Inventory.hh"
#include "Item.hh"

Inventory::Inventory() {
	//Initializes the inventory map to 0 for each item string
	for (auto i : Item::names()) {
		items_[i] = 0;
	}
	gold_ = 0;

        // TEST LINE -- remove eventually
        items_["Small Bomb"] = 20;
        items_["Large Bomb"] = 20;
        items_["Crucifix Bomb"] = 20;
        items_["Large Crucifix Bomb"] = 20;
        items_["Flamer"] = 10;
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

std::string Inventory::getNextItem(std::string const& name) const {
    // Try to find nonzero item between the given item and end()...
    auto it = items_.find(name);
    if (it != items_.end())
        while (++it != items_.end())
            if (it->second > 0) return it->first;

    // Try to find nonzero item between begin() and the given item...
    for (it = items_.begin(); it != items_.end(); it++) {
        if (it->second > 0)
            return it->first;
        if (it->first == name)
            return name;
    }

    return name;
}

size_t Inventory::getItemCount(std::string item) {
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

void Inventory::sellItem(std::string item) {
    items_[item] -= 1;
}

bool Inventory::useItem(std::string item, Map& map, MapBlock* mb, Direction dir) {
	if (items_[item] > 0) {
		items_[item] -= 1;

                if (item == "Small Bomb")
                        new NormalBomb(map, mb, item);
                else if (item == "Large Bomb")
                        new NormalBomb(map, mb, item);
                else if (item == "Crucifix Bomb")
                        new CrucifixBomb(map, mb, item);
                else if (item == "Large Crucifix Bomb")
                        new CrucifixBomb(map, mb, item);
                else if (item == "Flamer")
                        new Flamer(map, mb->getBlock(dir), dir);

               return true;
	}
	return false;
}

void Inventory::collect(Item* item) {
	if (Treasure* t = dynamic_cast<Treasure*>(item)) {
		increaseGold(t->getWorth());

		//the item's constructor informs all the other holders of this data that its being deleted.
		delete item;
	} else if (Weaponbox* w = dynamic_cast<Weaponbox*>(item)) {
        addItem(w->generateItem());

        delete item;
    }
}
