#include "Inventory.hh"
#include "Item.hh"
#include <algorithm>
#include <string>

Inventory::Inventory() {
	//Initializes the inventory map to 0 for each item string
	for (auto i : Item::allNames()) {
		items_[i] = 0;
	}
	gold_ = 0;

        // TEST LINE -- remove eventually
        items_["Small Bomb"] = 20;
        items_["Large Bomb"] = 20;
        items_["Crucifix Bomb"] = 20;
        items_["Large Crucifix Bomb"] = 20;
        items_["Flamer"] = 10;
        items_["Mine"] = 20;
        items_["Carpet Bomb"] = 20;
        items_["Pickaxe"] = 5;




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

std::string Inventory::getNextItem(std::string const& name) {
    // Try to find nonzero item between the given item and end()...
    std::vector<std::string> items = Item::names();

    std::vector<std::string>::iterator it = std::find(items.begin(), items.end(), name);
    if (it != items.end()) {
        while (++it != items.end()) {
            // if (std::find(pn.begin(), pn.end(), it->first) != pn.end()) continue;
            if (items_[*it] > 0) {
                return *it;
            }
        }
    }

    // Try to find nonzero item between begin() and the given item...
    for (it = items.begin(); it != items.end(); it++) {
        // if (std::find(pn.begin(), pn.end(), it->first) != pn.end()) continue;
        if (items_[*it] > 0) {
            return *it;
        } else if (*it == name) {
            return name;
        }
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
                else if (item == "Mine")
                        new Mine(map, mb);
                else if (item == "Carpet Bomb")
                        new CarpetBomb(map, mb, 6, true);

               return true;
	}
	return false;
}

bool Inventory::collect(Item* item) {
	if (Treasure* t = dynamic_cast<Treasure*>(item)) {
		increaseGold(t->getWorth());
        return true;
	} else if (Weaponbox* w = dynamic_cast<Weaponbox*>(item)) {
        for (int i = rand()%6; i > 0; i--) {
            addItem(w->generateItem());
        }
        return true;
    }
    return false;
}

int Inventory::getExtraMiningPower() {
    return items_["Pickaxe"]*40;
}
