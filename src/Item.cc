#include "Item.hh"
#include "Game.hh"
#include <vector>
#include <string>

/*
 * Contains item implementations
*/

Item::Item(Map& map,
     MapBlock* location,
     std::string name,
     bool passable,
     bool collectible) :
        mapref_(map),
        location_(location),
        name_(name),
        passable_(passable),
        collectible_(collectible),
        alive_(true) {
    // Register the item with the map and block.
    // The map object takes care of initializing this item's sprite.
    map.pushItem(this);
    location->pushItem(this);
    sprite_.setPosition(16*location->x_, 16*location->y_);
    // TODO: implement this properly
    sprite_.setTexture(map.getGame()->graphicsManager_.getTexture( "Goldbar.png" ));
}

Item::~Item() {
	//tell the game and the mapblock that this item is now deleted
	//map_.getGame().popItem(this);
	//location_.popItem(this);X
}

std::vector<std::string> Item::names() {
	return std::vector<std::string> {
		"Small Bomb"
	};
}
std::vector<std::string> Item::treasureNames() {
	return std::vector<std::string> {
		"Gold Bar"
	};
}

SmallBomb::SmallBomb(Map& map, MapBlock* location) : Weapon(map, location, "Small Bomb", false) {
	radius_ = 3;
	power_ = 1;
	fusetime_ = 2.0f;
}

void SmallBomb::update(float dt) {
	fusetime_ -= dt;

	if (fusetime_ <= 0 && alive_) {
		//Explode with radius_ and power_
		//Make surrounding map blocks take damage. 

		//map_.blast(location_, radius_, power_);
		//The map could also tell the game to draw explosion animations at each mapblock.
		//

		alive_ = false;
	}
}

Treasure::Treasure(Map& map, MapBlock* location, std::string name, int worth) : Item(map, location, name, true, true), worth_(worth) {
	//possibly some texture loading etc.
}
void Treasure::update(float) {
	//Animations?
}
